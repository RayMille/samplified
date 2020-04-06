//
//  TeapotComponent.h
//  Samplified
//
//  Created by Camille Koenders on 29.03.20.
//  Copyright © 2020 jocako. All rights reserved.
//

#ifndef TeapotComponent_h
#define TeapotComponent_h

#include "WavefrontObjFile.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class TeapotComponent   : public OpenGLAppComponent
{
public:
    //==============================================================================
    TeapotComponent() //TODO: Add parameters here such as rotation etc
    {
    }

    ~TeapotComponent() override
    {
        shutdownOpenGL();
    }

    void initialise() override
    {
        createShaders();
    }

    void shutdown() override
    {
        shader    .reset();
        shape     .reset();
        attributes.reset();
        uniforms  .reset();
        
    }

    

    Matrix3D<float> getProjectionMatrix() const
    {
        auto w = 20; // fov effect, je gößer desto mehr platz für object
        auto h = w * getLocalBounds().toFloat().getAspectRatio (false); // AspectRatio

        return Matrix3D<float>::fromFrustum (w, -w, -h, h, 5.0f, 70.0f); // near distance, far distance has to be fit to window size to avoid unwanted scaling
    }

    Matrix3D<float> getViewMatrix() const
    {
        Matrix3D<float> viewMatrix ({ 0.0f, 0.0f, -20.0f }); // x groß rechts klein links, y groß hoch klein runter , z je größer desto näher
        Matrix3D<float> rotationMatrix = viewMatrix.rotation ({ 0.0f, 3.14159f, 5.0f * std::sin(getFrameCounter() *0.01f)}); //getFrameCounter() * //3.14159f
        return rotationMatrix * viewMatrix;
    }

    void render() override
    {
        jassert (OpenGLHelpers::isContextActive());
        
        auto desktopScale = (float) openGLContext.getRenderingScale();
        Colour c = Colour(0.0f,1.0f,0.0f, 0.0f);

        OpenGLHelpers::clear (c);//(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        int b = 2;//roundToInt (desktopScale * getWidth());
        glViewport (0, 0, getWidth()*b,getHeight()*b);//getWidth(), getHeight()); ///this sets window used to render GL Object --> better is symetric

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
    }

    // Create shader, and link them to program. Shader are small code sniplets that run on GPU and therefore
    // are far more efficient. VertexShader are run less often than fragmentShader
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
        // Setting results from shader programs as member variables.
        Attributes (OpenGLContext& context, OpenGLShaderProgram& shaderProgram)
        {
            position      .reset (createAttribute (context, shaderProgram, "position"));
            normal        .reset (createAttribute (context, shaderProgram, "normal"));
            sourceColour  .reset (createAttribute (context, shaderProgram, "sourceColour"));
            textureCoordIn.reset (createAttribute (context, shaderProgram, "textureCoordIn"));
        }

        // VertexAttributeArrays tell openGL which attributes (type of objects) we are working with.
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
        // Combines Vertex Attributes with shader programm.
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
    // Uniforms are defined once and not for every vertice --> Save space.
    // Data is send to shader.
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

            if (shapeFile.load (dir.getChildFile ("Resources").getChildFile ("KNOB_3.obj")).wasOk())
                for (auto* s : shapeFile.shapes)
                    vertexBuffers.add (new VertexBuffer (context, *s));
        }

        // Actually draws elements with GL_TRIANGLES
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

                // Index buffer is used, to tell how vertices are supposed to be connected.
                // This avoids unnecessary memory by doubling vertices --> Ex. two trinagles to suqare.
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TeapotComponent)
};


#endif /* TeapotComponent_h */
