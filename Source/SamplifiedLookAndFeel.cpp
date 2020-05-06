/*
  ==============================================================================

    SamplifiedLookAndFeel.cpp
    Created: 24 Apr 2020 2:51:18pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include "SamplifiedLookAndFeel.h"

//==============================================================================
SamplifiedLookAndFeel :: SamplifiedLookAndFeel()
    {
        setColour(ListBox::backgroundColourId, Colours::black);
        setColour(ListBox::outlineColourId, Colours::black);
        
        setColour(DirectoryContentsDisplayComponent::textColourId, Colours::white);
        setColour(DirectoryContentsDisplayComponent::highlightColourId, Colours::black);
        setColour(DirectoryContentsDisplayComponent::highlightedTextColourId, Colours::white);
        
        setColour(ComboBox::outlineColourId, Colours::black);
        setColour(ComboBox::textColourId, Colours::white);
        setColour(ComboBox::backgroundColourId, Colours::black);
        setColour(ComboBox::arrowColourId, Colours::red);
        
        setColour(PopupMenu::backgroundColourId,              Colours::black);
        setColour(PopupMenu::textColourId,                    Colours::white);
        setColour(PopupMenu::headerTextColourId,              Colours::white);
        setColour(PopupMenu::highlightedTextColourId,         Colours::white);
        setColour(PopupMenu::highlightedBackgroundColourId,   Colours::darkgrey);
        
        setColour(FileBrowserComponent::currentPathBoxBackgroundColourId, Colours::black);
        setColour(FileBrowserComponent::currentPathBoxTextColourId, Colours::white);
        setColour(FileBrowserComponent::currentPathBoxArrowColourId, Colours::red);
        
        setColour(ScrollBar::thumbColourId, Colours::red.withAlpha(0.4f));
        
        setColour(TextButton::buttonColourId, Colours::black);
        
        treeviewPlusMinusBoxColour = Colours::red;
                
    }

static std::unique_ptr<Drawable> createDrawableFromSVG (const char* data)
{
    auto xml = parseXML (data);
    jassert (xml != nullptr);
    return Drawable::createFromSVG (*xml);
}

const Drawable* SamplifiedLookAndFeel::getDefaultFolderImage()
{
    if (folderImage == nullptr)
        folderImage = createDrawableFromSVG (R"svgdata(
                                             <svg id="Layer_2" data-name="Layer 2" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 99.25 70.54"><defs><style>.cls-1{fill:url(#linear-gradient);}.cls-2{fill:#ff0019;}</style><linearGradient id="linear-gradient" x1="49.62" y1="70.54" x2="49.62" y2="4.42" gradientUnits="userSpaceOnUse"><stop offset="0" stop-color="#7a000f"/><stop offset="0.2" stop-color="#7e0210"/><stop offset="0.39" stop-color="#890713"/><stop offset="0.58" stop-color="#9c1017"/><stop offset="0.76" stop-color="#b61d1e"/><stop offset="0.94" stop-color="#d82d27"/><stop offset="1" stop-color="#e6332a"/></linearGradient></defs><title>Untitled-1</title><rect class="cls-1" y="4.42" width="99.25" height="66.12" rx="9"/><path class="cls-2" d="M140.62,137.11H59.38a9,9,0,0,1-9-9V92.57a9,9,0,0,1,9-9H92.55c3.53,0,6.9-3.45,9.33-6l6.77-7.11a12.47,12.47,0,0,1,9.06-3.89h22.91a9,9,0,0,1,9,9v52.54A9,9,0,0,1,140.62,137.11Z" transform="translate(-50.38 -66.57)"/></svg>
                                             //<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:cc="http://web.resource.org/cc/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd" xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" version="1.1" baseProfile="full" width="480px" height="360px" viewBox="0 0 480 360" preserveAspectRatio="xMidYMid meet" id="svg_document" style="zoom: 1;"><!-- Created with macSVG - https://macsvg.org/ - https://github.com/dsward2/macsvg/ --><title id="svg_document_title">Untitled.svg</title><defs id="svg_document_defs"></defs><g id="main_group"><polyline points="111,135 111,254 111,254 111,254 342,255 341,103 246,104 206,136 " stroke="none" id="polyline3" stroke-width="3px" fill="#cc0004" transform=""></polyline></g><polyline points="165,415 167,416 29,352" stroke="none" id="polyline2" stroke-width="3px" fill="#cc0004" transform=""></polyline></svg>
)svgdata");

    return folderImage.get();
}

const Drawable* SamplifiedLookAndFeel::getDefaultDocumentFileImage()
{
    if (documentImage == nullptr)
        documentImage = createDrawableFromSVG (R"svgdata(
                                               <svg id="Layer_1" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 105.81 85.88"><defs><style>.cls-1{fill:#ff0019;}</style></defs><title>WAVE</title><path class="cls-1" d="M48,105c3.95,0,8.69.8,12.53-.23,2.56-.68,3.62-2.44,4.52-4.75.82-2.1,2.65-5.5,2.66-7.71,0-.24.4-.74.32-1-.29-.84-2.51-.83-2.85,0-.14.34.4,1.42.51,1.78l2.13,7.54L71.3,113c.64,2.28,4.29,2.49,4.82,0L83.6,77.69H78.77L89.8,126c.68,3,4.6,1.93,4.91-.67l7.79-64.93-4.91.67,11.1,81c.33,2.4,4.47,2.38,4.82,0l9.69-66.49h-4.82l12.47,40.76c.57,1.87,3.64,2.67,4.57.6,1.39-3.1,2.48-6.8,4.32-9.63,2.09-3.2,5.7-2.28,9.24-2.28,3.22,0,3.22-5,0-5-4.4,0-9.95-1-12.75,3.18-2.21,3.32-3.49,7.56-5.13,11.2l4.57.6L123.2,74.24c-.66-2.15-4.45-2.59-4.82,0l-9.69,66.49h4.82l-11.1-80.95c-.42-3-4.61-1.86-4.91.66l-7.79,64.93,4.91-.66-11-48.35c-.54-2.36-4.32-2.41-4.83,0L71.3,111.68h4.82L72.37,98.42c-.78-2.73-1.38-9.81-4.7-11-4.88-1.68-6,7.53-7.1,10.24s-2.17,2.31-5,2.31H48c-3.21,0-3.22,5,0,5Z" transform="translate(-45.58 -57.97)"/></svg>
                                               //<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:cc="http://web.resource.org/cc/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd" xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" version="1.1" baseProfile="full" width="480px" height="360px" viewBox="0 0 480 360" preserveAspectRatio="xMidYMid meet" id="svg_document" style="zoom: 1;"><!-- Created with macSVG - https://macsvg.org/ - https://github.com/dsward2/macsvg/ --><title id="svg_document_title">Untitled.svg</title><defs id="svg_document_defs"></defs><g id="main_group"></g><path stroke="#a40006" id="path2" stroke-width="10px" d="M187,180 C187,58 204,321 207,204 C210,87 214,270 224,194 C234,118 240,150 240,205 C240,260 257,166 257,166 " fill="none" transform=""></path></svg>
                                               )svgdata");

    return documentImage.get();
}

void SamplifiedLookAndFeel::drawFileBrowserRow (Graphics& g, int width, int height,
                                         const File&, const String& filename, Image* icon,
                                         const String& fileSizeDescription,
                                         const String& fileTimeDescription,
                                         bool isDirectory, bool isItemSelected,
                                         int /*itemIndex*/, DirectoryContentsDisplayComponent& dcc)
{
    auto fileListComp = dynamic_cast<Component*> (&dcc);

    if (isItemSelected)
        g.fillAll (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightColourId)
                                           : findColour (DirectoryContentsDisplayComponent::highlightColourId));

    const int x = 32;
    g.setColour (Colours::black);

  
    if (auto* d = isDirectory ? getDefaultFolderImage()
                              : getDefaultDocumentFileImage())
        d->drawWithin (g, Rectangle<float> (5.0f, 3.0f, 17.0f, 17.0f),
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
    
    if (isItemSelected)
        g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightedTextColourId)
                                             : findColour (DirectoryContentsDisplayComponent::highlightedTextColourId));
    else
        g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::textColourId)
                                             : findColour (DirectoryContentsDisplayComponent::textColourId));

    g.setFont (height * 0.7f);

    if (width > 450 && ! isDirectory)
    {
        auto sizeX = roundToInt (width * 0.7f);
        auto dateX = roundToInt (width * 0.8f);

        g.drawFittedText (filename,
                          x, 0, sizeX - x, height,
                          Justification::centredLeft, 1);

        g.setFont (height * 0.5f);
        g.setColour (Colours::darkgrey);

        if (! isDirectory)
        {
            g.drawFittedText (fileSizeDescription,
                              sizeX, 0, dateX - sizeX - 8, height,
                              Justification::centredRight, 1);

            g.drawFittedText (fileTimeDescription,
                              dateX, 0, width - 8 - dateX, height,
                              Justification::centredRight, 1);
        }
    }
    else
    {
        g.drawFittedText (filename,
                          x, 0, width - x, height,
                          Justification::centredLeft, 1);

    }
}


Button* SamplifiedLookAndFeel::createFileBrowserGoUpButton()
{
    auto goUpButton = new DrawableButton ("up", DrawableButton::ImageOnButtonBackground);

    Path arrowPath;
    arrowPath.addTriangle (0, 10,
                           10, 10,
                           5,  0);
    arrowPath = arrowPath.createPathWithRoundedCorners(3);
    
    DrawablePath arrowImage;
    arrowImage.setPath (arrowPath);
    arrowImage.setFill (findColour(FileBrowserComponent::currentPathBoxArrowColourId));

    goUpButton->setImages (&arrowImage);

    return goUpButton;
}


void SamplifiedLookAndFeel::layoutFileBrowserComponent (FileBrowserComponent& browserComp,
                                                 DirectoryContentsDisplayComponent* fileListComponent,
                                                 FilePreviewComponent* previewComp,
                                                 ComboBox* currentPathBox,
                                                 TextEditor* filenameBox,
                                                 Button* goUpButton)
{
    
    const int x = 8;
    auto w = browserComp.getWidth() - x - x;

    if (previewComp != nullptr)
    {
        auto previewWidth = w / 3;
        previewComp->setBounds (x + w - previewWidth, 0, previewWidth, browserComp.getHeight());
        previewComp->getName();

        w -= previewWidth + 4;
    }

    int y = 4;

    const int controlsHeight = 22;
    const int upButtonWidth = 30;

    currentPathBox->setBounds (x, y, w - upButtonWidth - 6, controlsHeight);
    currentPathBox->hidePopup();

    
    goUpButton->setBounds (x + w - upButtonWidth, y, upButtonWidth, controlsHeight);

    y += controlsHeight + 4;

    if (auto listAsComp = dynamic_cast<Component*> (fileListComponent))
    {
        listAsComp->setBounds (x, y, w, browserComp.getHeight() - y);
        y = listAsComp->getBottom() + 4;
    }
}

//Change the file selector (top left)
void SamplifiedLookAndFeel::drawComboBox (Graphics& g, int width, int height, const bool isMouseButtonDown,
                                   int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box)
{
    
    g.fillAll (findColour (ComboBox::backgroundColourId));

       if (box.isEnabled() && box.hasKeyboardFocus (false))
       {
           g.setColour (findColour (ComboBox::focusedOutlineColourId));
           g.drawRect (0, 0, width, height, 2);
       }
       else
       {
           g.setColour (findColour (ComboBox::outlineColourId));
           g.drawRect (0, 0, width, height);
       }

       if (box.isEnabled())
       {
           const float arrowX = 0.3f;
           const float arrowH = 0.4f;

           Path p;

           p.addTriangle (buttonX + buttonW * 0.5f, buttonY + buttonH * (0.40f + arrowH),
                          buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.26f,
                          buttonX + buttonW * arrowX,buttonY + buttonH * 0.26f);
           
           //buttonX + 5, buttonY + 10,
//                          buttonX , buttonY,
//                          buttonX + 10,buttonY );
           p = p.createPathWithRoundedCorners(3);
           

           g.setColour (findColour (ComboBox::arrowColourId));
           g.fillPath (p);
       }
    
}


void SamplifiedLookAndFeel::drawTreeviewPlusMinusBox (Graphics& g, const Rectangle<float>& area,
                                               Colour backgroundColour, bool isOpen, bool isMouseOver)
{
    Path p;
    p.addTriangle (0.0f, 0.0f, 1.0f, isOpen ? 0.0f : 0.5f, isOpen ? 0.5f : 0.0f, 1.0f);

    g.setColour (treeviewPlusMinusBoxColour.withAlpha (isMouseOver ? 0.5f : 0.3f));
    g.fillPath (p, p.getTransformToScaleToFit (area.reduced (2, area.getHeight() / 4), true));
}

Slider::SliderLayout SamplifiedLookAndFeel::getSliderLayout (Slider& slider)
{
    // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints
    
    int minXSpace = 0;
    int minYSpace = 0;
    
    auto textBoxPos = slider.getTextBoxPosition();
    
    if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
        minXSpace = 30;
    else
        minYSpace = 15;
    
    auto localBounds = slider.getLocalBounds();
    
    auto textBoxWidth  = jmax (0, jmin (slider.getTextBoxWidth(),  localBounds.getWidth() - minXSpace));
    auto textBoxHeight = jmax (0, jmin (slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));
    
    Slider::SliderLayout layout;
    
    // 2. set the textBox bounds
    
    if (textBoxPos != Slider::NoTextBox)
    {
        if (slider.isBar())
        {
            layout.textBoxBounds = localBounds;
        }
        else
        {
            layout.textBoxBounds.setWidth (textBoxWidth);
            layout.textBoxBounds.setHeight (textBoxHeight);
            
            if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX (0);
            else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX (localBounds.getWidth() - textBoxWidth);
            else /* above or below -> centre horizontally */ layout.textBoxBounds.setX ((localBounds.getWidth() - textBoxWidth) / 2);
            
            //if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY (0);
            layout.textBoxBounds.setY (localBounds.getHeight() - textBoxHeight);
            //else /* left or right -> centre vertically */    layout.textBoxBounds.setY ((localBounds.getHeight() - textBoxHeight) / 2);
        }
    }
    
    // 3. set the slider bounds
    
    layout.sliderBounds = localBounds;
    
    if (slider.isBar())
    {
        layout.sliderBounds.reduce (1, 1);   // bar border
    }
    else
    {
        layout.sliderBounds.removeFromBottom (textBoxHeight + 9);
        
        const int thumbIndent = getSliderThumbRadius (slider);
        
        if (slider.isHorizontal())    layout.sliderBounds.reduce (thumbIndent, 0);
        else if (slider.isVertical()) layout.sliderBounds.reduce (0, thumbIndent);
    }
    
    return layout;
}

Label* SamplifiedLookAndFeel::createSliderTextBox (Slider& slider)
{
    auto* l = LookAndFeel_V2::createSliderTextBox (slider);
    
//    if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
//                                                                              || slider.getSliderStyle() == Slider::LinearBarVertical))
//    {
        l->setColour (Label::textColourId, Colours::lightgrey);
        l->setColour (Label::outlineColourId, Colours::transparentWhite);
//    }
    
    return l;
}
