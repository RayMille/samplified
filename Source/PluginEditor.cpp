/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
/**
    This is a quick-and-dirty parser for the 3D OBJ file format.

    Just call load() and if there aren't any errors, the 'shapes' array should
    be filled with all the shape objects that were loaded from the file.
*/
class WavefrontObjFile
{
public:
    WavefrontObjFile() {}

    Result load (const String& objFileContent)
    {
        shapes.clear();
        return parseObjFile (StringArray::fromLines (objFileContent));
    }

    Result load (const File& file)
    {
        sourceFile = file;
        return load (file.loadFileAsString());
    }

    //==============================================================================
    typedef juce::uint32 Index;

    struct Vertex        { float x, y, z; };
    struct TextureCoord  { float x, y;    };

    struct Mesh
    {
        Array<Vertex> vertices, normals;
        Array<TextureCoord> textureCoords;
        Array<Index> indices;
    };

    struct Material
    {
        Material() noexcept
        {
            zerostruct (ambient);
            zerostruct (diffuse);
            zerostruct (specular);
            zerostruct (transmittance);
            zerostruct (emission);
        }

        String name;

        Vertex ambient, diffuse, specular, transmittance, emission;
        float shininess = 1.0f, refractiveIndex = 0.0f;

        String ambientTextureName, diffuseTextureName,
               specularTextureName, normalTextureName;

        StringPairArray parameters;
    };

    struct Shape
    {
        String name;
        Mesh mesh;
        Material material;
    };

    OwnedArray<Shape> shapes;

private:
    //==============================================================================
    File sourceFile;

    struct TripleIndex
    {
        TripleIndex() noexcept {}

        bool operator< (const TripleIndex& other) const noexcept
        {
            if (this == &other)
                return false;

            if (vertexIndex != other.vertexIndex)
                return vertexIndex < other.vertexIndex;

            if (textureIndex != other.textureIndex)
                return textureIndex < other.textureIndex;

            return normalIndex < other.normalIndex;
        }

        int vertexIndex = -1, textureIndex = -1, normalIndex = -1;
    };

    struct IndexMap
    {
        std::map<TripleIndex, Index> map;

        Index getIndexFor (TripleIndex i, Mesh& newMesh, const Mesh& srcMesh)
        {
            const std::map<TripleIndex, Index>::iterator it (map.find (i));

            if (it != map.end())
                return it->second;

            auto index = (Index) newMesh.vertices.size();

            if (isPositiveAndBelow (i.vertexIndex, srcMesh.vertices.size()))
                newMesh.vertices.add (srcMesh.vertices.getReference (i.vertexIndex));

            if (isPositiveAndBelow (i.normalIndex, srcMesh.normals.size()))
                newMesh.normals.add (srcMesh.normals.getReference (i.normalIndex));

            if (isPositiveAndBelow (i.textureIndex, srcMesh.textureCoords.size()))
                newMesh.textureCoords.add (srcMesh.textureCoords.getReference (i.textureIndex));

            map[i] = index;
            return index;
        }
    };

    static float parseFloat (String::CharPointerType& t)
    {
        t = t.findEndOfWhitespace();
        return (float) CharacterFunctions::readDoubleValue (t);
    }

    static Vertex parseVertex (String::CharPointerType t)
    {
        Vertex v;
        v.x = parseFloat (t);
        v.y = parseFloat (t);
        v.z = parseFloat (t);
        return v;
    }

    static TextureCoord parseTextureCoord (String::CharPointerType t)
    {
        TextureCoord tc;
        tc.x = parseFloat (t);
        tc.y = parseFloat (t);
        return tc;
    }

    static bool matchToken (String::CharPointerType& t, const char* token)
    {
        auto len = (int) strlen (token);

        if (CharacterFunctions::compareUpTo (CharPointer_ASCII (token), t, len) == 0)
        {
            auto end = t + len;

            if (end.isEmpty() || end.isWhitespace())
            {
                t = end.findEndOfWhitespace();
                return true;
            }
        }

        return false;
    }

    struct Face
    {
        Face (String::CharPointerType t)
        {
            while (! t.isEmpty())
                triples.add (parseTriple (t));
        }

        Array<TripleIndex> triples;

        void addIndices (Mesh& newMesh, const Mesh& srcMesh, IndexMap& indexMap)
        {
            TripleIndex i0 (triples[0]), i1, i2 (triples[1]);

            for (auto i = 2; i < triples.size(); ++i)
            {
                i1 = i2;
                i2 = triples.getReference (i);

                newMesh.indices.add (indexMap.getIndexFor (i0, newMesh, srcMesh));
                newMesh.indices.add (indexMap.getIndexFor (i1, newMesh, srcMesh));
                newMesh.indices.add (indexMap.getIndexFor (i2, newMesh, srcMesh));
            }
        }

        static TripleIndex parseTriple (String::CharPointerType& t)
        {
            TripleIndex i;

            t = t.findEndOfWhitespace();
            i.vertexIndex = t.getIntValue32() - 1;
            t = findEndOfFaceToken (t);

            if (t.isEmpty() || t.getAndAdvance() != '/')
                return i;

            if (*t == '/')
            {
                ++t;
            }
            else
            {
                i.textureIndex = t.getIntValue32() - 1;
                t = findEndOfFaceToken (t);

                if (t.isEmpty() || t.getAndAdvance() != '/')
                    return i;
            }

            i.normalIndex = t.getIntValue32() - 1;
            t = findEndOfFaceToken (t);
            return i;
        }

        static String::CharPointerType findEndOfFaceToken (String::CharPointerType t) noexcept
        {
            return CharacterFunctions::findEndOfToken (t, CharPointer_ASCII ("/ \t"), String().getCharPointer());
        }
    };

    static Shape* parseFaceGroup (const Mesh& srcMesh,
                                  Array<Face>& faceGroup,
                                  const Material& material,
                                  const String& name)
    {
        if (faceGroup.size() == 0)
            return nullptr;

        std::unique_ptr<Shape> shape (new Shape());
        shape->name = name;
        shape->material = material;

        IndexMap indexMap;

        for (auto& f : faceGroup)
            f.addIndices (shape->mesh, srcMesh, indexMap);

        return shape.release();
    }

    Result parseObjFile (const StringArray& lines)
    {
        Mesh mesh;
        Array<Face> faceGroup;

        Array<Material> knownMaterials;
        Material lastMaterial;
        String lastName;

        for (auto lineNum = 0; lineNum < lines.size(); ++lineNum)
        {
            auto l = lines[lineNum].getCharPointer().findEndOfWhitespace();

            if (matchToken (l, "v"))    { mesh.vertices.add (parseVertex (l));            continue; }
            if (matchToken (l, "vn"))   { mesh.normals.add (parseVertex (l));             continue; }
            if (matchToken (l, "vt"))   { mesh.textureCoords.add (parseTextureCoord (l)); continue; }
            if (matchToken (l, "f"))    { faceGroup.add (Face (l));                       continue; }

            if (matchToken (l, "usemtl"))
            {
                auto name = String (l).trim();

                for (auto i = knownMaterials.size(); --i >= 0;)
                {
                    if (knownMaterials.getReference(i).name == name)
                    {
                        lastMaterial = knownMaterials.getReference(i);
                        break;
                    }
                }

                continue;
            }

            if (matchToken (l, "mtllib"))
            {
                Result r = parseMaterial (knownMaterials, String (l).trim());
                continue;
            }

            if (matchToken (l, "g") || matchToken (l, "o"))
            {
                if (Shape* shape = parseFaceGroup (mesh, faceGroup, lastMaterial, lastName))
                    shapes.add (shape);

                faceGroup.clear();
                lastName = StringArray::fromTokens (l, " \t", "")[0];
                continue;
            }
        }

        if (auto* shape = parseFaceGroup (mesh, faceGroup, lastMaterial, lastName))
            shapes.add (shape);

        return Result::ok();
    }

    Result parseMaterial (Array<Material>& materials, const String& filename)
    {
        jassert (sourceFile.exists());
        auto f = sourceFile.getSiblingFile (filename);

        if (! f.exists())
            return Result::fail ("Cannot open file: " + filename);

        auto lines = StringArray::fromLines (f.loadFileAsString());

        materials.clear();
        Material material;

        for (auto line : lines)
        {
            auto l = line.getCharPointer().findEndOfWhitespace();

            if (matchToken (l, "newmtl"))   { materials.add (material); material.name = String (l).trim(); continue; }

            if (matchToken (l, "Ka"))       { material.ambient         = parseVertex (l); continue; }
            if (matchToken (l, "Kd"))       { material.diffuse         = parseVertex (l); continue; }
            if (matchToken (l, "Ks"))       { material.specular        = parseVertex (l); continue; }
            if (matchToken (l, "Kt"))       { material.transmittance   = parseVertex (l); continue; }
            if (matchToken (l, "Ke"))       { material.emission        = parseVertex (l); continue; }
            if (matchToken (l, "Ni"))       { material.refractiveIndex = parseFloat (l);  continue; }
            if (matchToken (l, "Ns"))       { material.shininess       = parseFloat (l);  continue; }

            if (matchToken (l, "map_Ka"))   { material.ambientTextureName  = String (l).trim(); continue; }
            if (matchToken (l, "map_Kd"))   { material.diffuseTextureName  = String (l).trim(); continue; }
            if (matchToken (l, "map_Ks"))   { material.specularTextureName = String (l).trim(); continue; }
            if (matchToken (l, "map_Ns"))   { material.normalTextureName   = String (l).trim(); continue; }

            auto tokens = StringArray::fromTokens (l, " \t", "");

            if (tokens.size() >= 2)
                material.parameters.set (tokens[0].trim(), tokens[1].trim());
        }

        materials.add (material);
        return Result::ok();
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavefrontObjFile)
};




//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class GLComponent   : public OpenGLAppComponent
{
public:
    //==============================================================================
    GLComponent() //TODO: Add parameters here such as rotation etc
    {
        setSize(600,600);
        
        
    }

    ~GLComponent() override
    {
        
    }

    void initialise() override
    {
        createShaders();
       // openGLContext.attachTo(*this);
    }

    void shutdown() override
    {
        shader    .reset();
        shape     .reset();
        attributes.reset();
        uniforms  .reset();
     //   openGLContext.detach();
        
    }

    

    Matrix3D<float> getProjectionMatrix() const
    {
        auto w = 1.0f / (0.5f + 0.1f);
        auto h = w * getLocalBounds().toFloat().getAspectRatio (false);

        return Matrix3D<float>::fromFrustum (-w, w, -h, h, 4.0f, 30.0f);
    }

    Matrix3D<float> getViewMatrix() const
    {
        Matrix3D<float> viewMatrix ({ 0.0f, 0.0f, -30.0f });
        Matrix3D<float> rotationMatrix = viewMatrix.rotation ({ -0.3f, 5.0f * std::sin ( getFrameCounter() * 0.01f), 0.0f });

        return  rotationMatrix * viewMatrix;
    }

    void render() override
    {
        jassert (OpenGLHelpers::isContextActive());

        auto desktopScale = (float) openGLContext.getRenderingScale();
        OpenGLHelpers::clear (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport (0, 0, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()));

        shader->use();

        if (uniforms->projectionMatrix.get() != nullptr)
            uniforms->projectionMatrix->setMatrix4 (getProjectionMatrix().mat, 1, false);

        if (uniforms->viewMatrix.get() != nullptr)
            uniforms->viewMatrix->setMatrix4 (getViewMatrix().mat, 1, false);

        shape->draw (openGLContext, *attributes);

        // Reset the element buffers so child Components draw correctly
        openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, 0);
        openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

    }

    void paint (Graphics& g) override
    {
        // You can add your component specific drawing code here!
        // This will draw over the top of the openGL background.

        g.setColour (getLookAndFeel().findColour (Label::textColourId));
        g.setFont (20);
        g.drawText ("OpenGL Example", 25, 20, 300, 30, Justification::left);
        g.drawLine (20, 20, 170, 20);
        g.drawLine (20, 50, 170, 50);
    }

    void createShaders()
    {
        vertexShader =
            "attribute vec4 position;\n"
            "attribute vec4 sourceColour;\n"
            "attribute vec2 textureCoordIn;\n"
            "\n"
            "uniform mat4 projectionMatrix;\n"
            "uniform mat4 viewMatrix;\n"
            "\n"
            "varying vec4 destinationColour;\n"
            "varying vec2 textureCoordOut;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    destinationColour = sourceColour;\n"
            "    textureCoordOut = textureCoordIn;\n"
            "    gl_Position = projectionMatrix * viewMatrix * position;\n"
            "}\n";

        fragmentShader =
           #if JUCE_OPENGL_ES
            "varying lowp vec4 destinationColour;\n"
            "varying lowp vec2 textureCoordOut;\n"
           #else
            "varying vec4 destinationColour;\n"
            "varying vec2 textureCoordOut;\n"
           #endif
            "\n"
            "void main()\n"
            "{\n"
           #if JUCE_OPENGL_ES
            "    lowp vec4 colour = vec4(0.95, 0.57, 0.03, 0.7);\n"
           #else
            "    vec4 colour = vec4(0.95, 0.57, 0.03, 0.7);\n"
           #endif
            "    gl_FragColor = colour;\n"
            "}\n";

        std::unique_ptr<OpenGLShaderProgram> newShader (new OpenGLShaderProgram (openGLContext));
        String statusText;

        if (newShader->addVertexShader (OpenGLHelpers::translateVertexShaderToV3 (vertexShader))
              && newShader->addFragmentShader (OpenGLHelpers::translateFragmentShaderToV3 (fragmentShader))
              && newShader->link())
        {
            shape     .reset();
            attributes.reset();
            uniforms  .reset();

            shader.reset (newShader.release());
            shader->use();

            shape     .reset (new Shape (openGLContext));
            attributes.reset (new Attributes (openGLContext, *shader));
            uniforms  .reset (new Uniforms (openGLContext, *shader));

            statusText = "GLSL: v" + String (OpenGLShaderProgram::getLanguageVersion(), 2);
        }
        else
        {
            statusText = newShader->getLastError();
        }
    }
    
    OpenGLContext openGLContext;

private:
    //==============================================================================
    struct Vertex
    {
        float position[3];
        float normal[3];
        float colour[4];
        float texCoord[2];
    };

    //==============================================================================
    // This class just manages the attributes that the shaders use.
    struct Attributes
    {
        Attributes (OpenGLContext& context, OpenGLShaderProgram& shaderProgram)
        {
            position      .reset (createAttribute (context, shaderProgram, "position"));
            normal        .reset (createAttribute (context, shaderProgram, "normal"));
            sourceColour  .reset (createAttribute (context, shaderProgram, "sourceColour"));
            textureCoordIn.reset (createAttribute (context, shaderProgram, "textureCoordIn"));
        }

        void enable (OpenGLContext& context)
        {
            if (position.get() != nullptr)
            {
                context.extensions.glVertexAttribPointer (position->attributeID, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), 0);
                context.extensions.glEnableVertexAttribArray (position->attributeID);
            }

            if (normal.get() != nullptr)
            {
                context.extensions.glVertexAttribPointer (normal->attributeID, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 3));
                context.extensions.glEnableVertexAttribArray (normal->attributeID);
            }

            if (sourceColour.get() != nullptr)
            {
                context.extensions.glVertexAttribPointer (sourceColour->attributeID, 4, GL_FLOAT, GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 6));
                context.extensions.glEnableVertexAttribArray (sourceColour->attributeID);
            }

            if (textureCoordIn.get() != nullptr)
            {
                context.extensions.glVertexAttribPointer (textureCoordIn->attributeID, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 10));
                context.extensions.glEnableVertexAttribArray (textureCoordIn->attributeID);
            }
        }

        void disable (OpenGLContext& context)
        {
            if (position.get() != nullptr)       context.extensions.glDisableVertexAttribArray (position->attributeID);
            if (normal.get() != nullptr)         context.extensions.glDisableVertexAttribArray (normal->attributeID);
            if (sourceColour.get() != nullptr)   context.extensions.glDisableVertexAttribArray (sourceColour->attributeID);
            if (textureCoordIn.get() != nullptr) context.extensions.glDisableVertexAttribArray (textureCoordIn->attributeID);
        }

        std::unique_ptr<OpenGLShaderProgram::Attribute> position, normal, sourceColour, textureCoordIn;

    private:
        static OpenGLShaderProgram::Attribute* createAttribute (OpenGLContext& context,
                                                                OpenGLShaderProgram& shader,
                                                                const String& attributeName)
        {
            if (context.extensions.glGetAttribLocation (shader.getProgramID(), attributeName.toRawUTF8()) < 0)
                return nullptr;

            return new OpenGLShaderProgram::Attribute (shader, attributeName.toRawUTF8());
        }
    };

    //==============================================================================
    // This class just manages the uniform values that the demo shaders use.
    struct Uniforms
    {
        Uniforms (OpenGLContext& context, OpenGLShaderProgram& shaderProgram)
        {
            projectionMatrix.reset (createUniform (context, shaderProgram, "projectionMatrix"));
            viewMatrix      .reset (createUniform (context, shaderProgram, "viewMatrix"));
        }

        std::unique_ptr<OpenGLShaderProgram::Uniform> projectionMatrix, viewMatrix;

    private:
        static OpenGLShaderProgram::Uniform* createUniform (OpenGLContext& context,
                                                            OpenGLShaderProgram& shaderProgram,
                                                            const String& uniformName)
        {
            if (context.extensions.glGetUniformLocation (shaderProgram.getProgramID(), uniformName.toRawUTF8()) < 0)
                return nullptr;

            return new OpenGLShaderProgram::Uniform (shaderProgram, uniformName.toRawUTF8());
        }
    };

    //==============================================================================
    /** This loads a 3D model from an OBJ file and converts it into some vertex buffers
        that we can draw.
    */
    struct Shape
    {
        Shape (OpenGLContext& context)
        {
            auto dir = File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory);

            int numTries = 0;

            while (! dir.getChildFile ("Resources").exists() && numTries++ < 15)
                dir = dir.getParentDirectory();

            if (shapeFile.load (dir.getChildFile ("Resources").getChildFile ("KNOB_1.obj")).wasOk())
                for (auto* s : shapeFile.shapes)
                    vertexBuffers.add (new VertexBuffer (context, *s));
        }

        void draw (OpenGLContext& context, Attributes& glAttributes)
        {
            for (auto* vertexBuffer : vertexBuffers)
            {
                vertexBuffer->bind();

                glAttributes.enable (context);
                glDrawElements (GL_TRIANGLES, vertexBuffer->numIndices, GL_UNSIGNED_INT, 0);
                glAttributes.disable (context);
            }
        }

    private:
        struct VertexBuffer
        {
            VertexBuffer (OpenGLContext& context, WavefrontObjFile::Shape& aShape) : openGLContext (context)
            {
                numIndices = aShape.mesh.indices.size();

                openGLContext.extensions.glGenBuffers (1, &vertexBuffer);
                openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);

                Array<Vertex> vertices;
                createVertexListFromMesh (aShape.mesh, vertices, Colours::green);

                openGLContext.extensions.glBufferData (GL_ARRAY_BUFFER,
                                                       static_cast<GLsizeiptr> (static_cast<size_t> (vertices.size()) * sizeof (Vertex)),
                                                       vertices.getRawDataPointer(), GL_STATIC_DRAW);

                openGLContext.extensions.glGenBuffers (1, &indexBuffer);
                openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
                openGLContext.extensions.glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                                                       static_cast<GLsizeiptr> (static_cast<size_t> (numIndices) * sizeof (juce::uint32)),
                                                       aShape.mesh.indices.getRawDataPointer(), GL_STATIC_DRAW);
            }

            ~VertexBuffer()
            {
                openGLContext.extensions.glDeleteBuffers (1, &vertexBuffer);
                openGLContext.extensions.glDeleteBuffers (1, &indexBuffer);
            }

            void bind()
            {
                openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
                openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            }

            GLuint vertexBuffer, indexBuffer;
            int numIndices;
            OpenGLContext& openGLContext;

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VertexBuffer)
        };

        WavefrontObjFile shapeFile;
        OwnedArray<VertexBuffer> vertexBuffers;

        static void createVertexListFromMesh (const WavefrontObjFile::Mesh& mesh, Array<Vertex>& list, Colour colour)
        {
            auto scale = 0.2f;
            WavefrontObjFile::TextureCoord defaultTexCoord { 0.5f, 0.5f };
            WavefrontObjFile::Vertex defaultNormal { 0.5f, 0.5f, 0.5f };

            for (auto i = 0; i < mesh.vertices.size(); ++i)
            {
                const auto& v = mesh.vertices.getReference (i);
                const auto& n = i < mesh.normals.size() ? mesh.normals.getReference (i) : defaultNormal;
                const auto& tc = i < mesh.textureCoords.size() ? mesh.textureCoords.getReference (i) : defaultTexCoord;

                list.add ({ { scale * v.x, scale * v.y, scale * v.z, },
                            { scale * n.x, scale * n.y, scale * n.z, },
                            { colour.getFloatRed(), colour.getFloatGreen(), colour.getFloatBlue(), colour.getFloatAlpha() },
                            { tc.x, tc.y } });
            }
        }
    };

    String vertexShader;
    String fragmentShader;

    std::unique_ptr<OpenGLShaderProgram> shader;
    std::unique_ptr<Shape> shape;
    std::unique_ptr<Attributes> attributes;
    std::unique_ptr<Uniforms> uniforms;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GLComponent)
};






//==============================================================================
PluginSynthWithFileUploadAudioProcessorEditor::PluginSynthWithFileUploadAudioProcessorEditor (PluginSynthWithFileUploadAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);
    
}

PluginSynthWithFileUploadAudioProcessorEditor::~PluginSynthWithFileUploadAudioProcessorEditor()
{
    processor.m_fileBrowser->removeListener(this);
    glComponent = nullptr;
}

//==============================================================================
void PluginSynthWithFileUploadAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    
    glComponent = new GLComponent;
    addAndMakeVisible (glComponent);
//    addAndMakeVisible(processor.m_fileBrowser);
//    processor.m_fileBrowser->setTopLeftPosition(150, 150);
//    processor.m_fileBrowser->setSize(300, 300);
//    processor.m_fileBrowser->addListener(this);
}

void PluginSynthWithFileUploadAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//==============================================================================
void PluginSynthWithFileUploadAudioProcessorEditor::selectionChanged ()
{
}

void PluginSynthWithFileUploadAudioProcessorEditor::fileClicked (const File& file, const MouseEvent& e)
{
    if(processor.m_fileBrowser->currentFileIsValid()){
        processor.loadNewSample(processor.m_fileBrowser->getSelectedFile(0));
    }
          
    //    auto* reader = formatManager.createReaderFor (file);
    //
    //    if (reader != nullptr)
    //    {
    //        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
    //        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
    //        readerSource.reset (newSource.release());
    //    }
}

void PluginSynthWithFileUploadAudioProcessorEditor::fileDoubleClicked (const File& file)
{
}

void PluginSynthWithFileUploadAudioProcessorEditor::browserRootChanged (const File& newRoot)
{
}
