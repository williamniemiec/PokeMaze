#include "pokemaze/engine/Display.hpp"
#include "pokemaze/engine/text/TextRender.hpp"

Display::Display(GLFWwindow* window)
{
    this->window = window;
    text_renderer = new TextRender();
}

void Display::show_controls()
{
    float pad = text_renderer->TextRendering_LineHeight(window);

    char buffer[80];
    snprintf(buffer, 80, "Controls: W,A,S,D: Move | C: Free camera / Fixed camera | Pause Break: Pause");

    text_renderer->TextRendering_PrintString(window, buffer, -1.0f+pad/10, -1.0f+2*pad/10, 1.0f);
}

void Display::show_pause()
{
    float pad = text_renderer->TextRendering_LineHeight(window);
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    text_renderer->TextRendering_PrintString(window, "PAUSED", -0.33+pad, -0.1+pad, 5.0f);
}

void Display::show_projection(bool is_perspective)
{
    float lineheight = text_renderer->TextRendering_LineHeight(window);
    float charwidth = text_renderer->TextRendering_CharWidth(window);

    if (is_perspective)
        text_renderer->TextRendering_PrintString(window, "Perspective", 1.0f-13*charwidth, -1.0f+2*lineheight/10, 1.0f);
    else
        text_renderer->TextRendering_PrintString(window, "Orthographic", 1.0f-13*charwidth, -1.0f+2*lineheight/10, 1.0f);
}

void Display::show_fps()
{
    static float old_seconds = (float)glfwGetTime();
    static int   ellapsed_frames = 0;
    static char  buffer[20] = "?? fps";
    static int   numchars = 7;

    ellapsed_frames += 1;

    // Recuperamos o número de segundos que passou desde a execução do programa
    float seconds = (float)glfwGetTime();

    // Número de segundos desde o último cálculo do fps
    float ellapsed_seconds = seconds - old_seconds;

    if ( ellapsed_seconds > 1.0f )
    {
        numchars = snprintf(buffer, 20, "%.2f fps", ellapsed_frames / ellapsed_seconds);

        old_seconds = seconds;
        ellapsed_frames = 0;
    }

    float lineheight = text_renderer->TextRendering_LineHeight(window);
    float charwidth = text_renderer->TextRendering_CharWidth(window);

    text_renderer->TextRendering_PrintString(window, buffer, 1.0f-(numchars + 1)*charwidth, 1.0f-lineheight, 1.0f);
}
