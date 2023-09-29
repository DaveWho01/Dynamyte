#include "PresetManager.h"

PresetManager::PresetManager(AudioProcessorValueTreeState& APVTS, DynamyteAudioProcessor& p)
    :   pluginState(APVTS), processor(p)
{
    defaultDir = File::getSpecialLocation(File::SpecialLocationType::commonDocumentsDirectory)
        .getChildFile(ProjectInfo::companyName)
        .getChildFile(ProjectInfo::projectName);
    extension = ".xml";
    currentPreset = "-- No preset selected --";

    if (!defaultDir.exists())
    {
        auto res = defaultDir.createDirectory();
        if (res.failed())
        {
            DBG("Error creating default directory" + res.getErrorMessage());
            jassertfalse;
        }
    }
}

PresetManager::~PresetManager()
{
}

void PresetManager::loadPreset()
{
    FileChooser chooser("Select preset to load...", defaultDir, "*" + extension);
    if (chooser.browseForFileToOpen())
    {
        auto presetFile = chooser.getResult();
        MemoryBlock sourceData;
        presetFile.loadFileAsData(sourceData);
        processor.setStateInformation(sourceData.getData(), sourceData.getSize());
        currentPreset = presetFile.getFileNameWithoutExtension();
    }
}

void PresetManager::savePreset()
{
    FileChooser chooser("Select save position...", defaultDir, "*" + extension);
    if (chooser.browseForFileToSave(true))
    {
        auto presetFile = chooser.getResult();
        if (presetFile.exists())
            presetFile.deleteFile();
        FileOutputStream outputStream(presetFile);
        if (outputStream.openedOk())
        {
            MemoryBlock destData;
            processor.getStateInformation(destData);
            outputStream.write(destData.getData(), destData.getSize());
        }
    }
}

String PresetManager::getCurrentPreset()
{
    return currentPreset;
}

StringArray PresetManager::getAllPresets()
{
    StringArray presets;
    const auto fileArray = defaultDir.findChildFiles(
        File::TypesOfFileToFind::findFiles, true, "*" + extension);
    for (auto& file : fileArray)
        presets.add(file.getFileNameWithoutExtension());

    return presets;
}

void PresetManager::loadNextPreset()
{
    auto presets = getAllPresets();
    if (!presets.isEmpty())
    {
        auto currentIndex = presets.indexOf(currentPreset);
        auto nextIndex = currentIndex + 1 > (presets.size() - 1) ? 0 : currentIndex + 1;

        auto presetFile = defaultDir.findChildFiles(
            File::TypesOfFileToFind::findFiles, true, presets[nextIndex] + extension)[0];
        MemoryBlock sourceData;
        presetFile.loadFileAsData(sourceData);
        processor.setStateInformation(sourceData.getData(), sourceData.getSize());
        currentPreset = presetFile.getFileNameWithoutExtension();
    }
}

void PresetManager::loadPreviousPreset()
{
    auto presets = getAllPresets();
    if (!presets.isEmpty())
    {
        auto currentIndex = presets.indexOf(currentPreset);
        auto prevIndex = currentIndex - 1 < 0 ? presets.size() - 1 : currentIndex - 1;

        auto presetFile = defaultDir.findChildFiles(
            File::TypesOfFileToFind::findFiles, true, presets[prevIndex] + extension)[0];
        MemoryBlock sourceData;
        presetFile.loadFileAsData(sourceData);
        processor.setStateInformation(sourceData.getData(), sourceData.getSize());
        currentPreset = presetFile.getFileNameWithoutExtension();
    }
}
