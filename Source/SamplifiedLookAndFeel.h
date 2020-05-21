/*
  ==============================================================================

    SamplifiedLookAndFeel.h
    Created: 24 Apr 2020 2:51:30pm
    Author:  Camille Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SamplifiedLookAndFeel    : public LookAndFeel_V4

{
public:
    SamplifiedLookAndFeel();
    
    
    const Drawable* getDefaultFolderImage() override;
    const Drawable* getDefaultDocumentFileImage() override;
    
    void layoutFileBrowserComponent (FileBrowserComponent& browserComp, DirectoryContentsDisplayComponent* fileListComponent, FilePreviewComponent* previewComp, ComboBox* currentPathBox, TextEditor* filenameBox, Button* goUpButton) override;
    
    void drawFileBrowserRow (Graphics& g, int width, int height, const File&, const String& filename, Image* icon, const String& fileSizeDescription, const String& fileTimeDescription, bool isDirectory, bool isItemSelected, int /*itemIndex*/, DirectoryContentsDisplayComponent& dcc) override;

    void drawComboBox (Graphics& g, int width, int height, const bool isMouseButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box) override;
    
    Button* createFileBrowserGoUpButton() override;
    
    void drawTreeviewPlusMinusBox (Graphics& g, const Rectangle<float>& area, Colour backgroundColour, bool isOpen, bool isMouseOver) override;
    
    Slider::SliderLayout getSliderLayout (Slider& slider) override;
    
    Label* createSliderTextBox (Slider& slider) override;
    
    Colour treeviewPlusMinusBoxColour;
    
    void drawLabel (Graphics& g, Label& label) override;
    

private:
    std::unique_ptr<Drawable> folderImage, documentImage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedLookAndFeel)
};
