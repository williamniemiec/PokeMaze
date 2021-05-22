#include "pokemaze/engine/Display.hpp"
#include "pokemaze/engine/text/TextRender.hpp"

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
int Display::screen_width;
int Display::screen_height;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Display::Display(GLFWwindow* window)
{
    this->window = window;
    text_renderer = new TextRender();

    glfwGetWindowSize(window, &screen_width, &screen_height);
    glfwSetFramebufferSizeCallback(window, window_resize_handler);
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void Display::show_controls()
{
    float pad = text_renderer->TextRendering_LineHeight(window);

    char buffer[80];
    snprintf(buffer, 80, "Controls: W,A,S,D: Move | C: Free camera / Fixed camera | Pause Break: Pause");

    text_renderer->TextRendering_PrintString(
            window,
            buffer,
            -1.0f+pad/10,
            -1.0f+2*pad/10,
            1.0f
    );
}

void Display::show_pause()
{
    float pad = text_renderer->TextRendering_LineHeight(window);
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    text_renderer->TextRendering_PrintString(
            window,
            "PAUSED",
            -0.33+pad,
            -0.1+pad,
            5.0f
    );
}

void Display::show_projection(bool is_perspective)
{
    float lineheight = text_renderer->TextRendering_LineHeight(window);
    float charwidth = text_renderer->TextRendering_CharWidth(window);
    std::string projection_type = is_perspective ? "Perspective" : "Orthographic";

    text_renderer->TextRendering_PrintString(
            window,
            projection_type,
            1.0f-13*charwidth,
            -1.0f+2*lineheight/10,
            1.0f
    );
}

void Display::show_fps()
{
    static float old_seconds = (float)glfwGetTime();
    static int   ellapsed_frames = 0;
    static char  buffer[20] = "?? fps";
    static int   numchars = 7;

    ellapsed_frames += 1;

    float seconds = (float)glfwGetTime();
    float ellapsed_seconds = seconds - old_seconds;

    if (ellapsed_seconds > 1.0f)
    {
        numchars = snprintf(buffer, 20, "%.2f fps", ellapsed_frames / ellapsed_seconds);

        old_seconds = seconds;
        ellapsed_frames = 0;
    }

    float lineheight = text_renderer->TextRendering_LineHeight(window);
    float charwidth = text_renderer->TextRendering_CharWidth(window);

    text_renderer->TextRendering_PrintString(
            window,
            buffer,
            1.0f-(numchars + 1)*charwidth,
            1.0f-lineheight, 1.0f
    );
}

void Display::show_gpu()
{
    const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *glversion = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);
}

void Display::window_resize_handler(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    screen_width = width;
    screen_height = height;
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
int Display::get_screen_width()
{
    return screen_width;
}

int Display::get_screen_height()
{
    return screen_height;
}
