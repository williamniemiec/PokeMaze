#include "pokemaze/util/algebra/Matrices.hpp"

using namespace pokemaze::util::algebra;


glm::mat4 Matrices::matrix(
    float m00, float m01, float m02, float m03, // LINHA 1
    float m10, float m11, float m12, float m13, // LINHA 2
    float m20, float m21, float m22, float m23, // LINHA 3
    float m30, float m31, float m32, float m33  // LINHA 4
)
{

    return glm::mat4(
        m00, m10, m20, m30, // COLUNA 1
        m01, m11, m21, m31, // COLUNA 2
        m02, m12, m22, m32, // COLUNA 3
        m03, m13, m23, m33  // COLUNA 4
    );
}

// FONTE: https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix/1148405
glm::mat4 Matrices::inverse_4x4(glm::mat4 m)
{
    float A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
    float A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
    float A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
    float A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
    float A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
    float A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
    float A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
    float A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
    float A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
    float A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
    float A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
    float A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    float A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
    float A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
    float A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
    float A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
    float A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
    float A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

    float det = m[0][0] * ( m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223 )
        - m[0][1] * ( m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223 )
        + m[0][2] * ( m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123 )
        - m[0][3] * ( m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123 ) ;
    det = 1 / det;

   float m00 = det *   ( m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223 );
   float m01 = det * - ( m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223 );
   float m02 = det *   ( m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213 );
   float m03 = det * - ( m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212 );
   float m10 = det * - ( m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223 );
   float m11 = det *   ( m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223 );
   float m12 = det * - ( m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213 );
   float m13 = det *   ( m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212 );
   float m20 = det *   ( m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123 );
   float m21 = det * - ( m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123 );
   float m22 = det *   ( m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113 );
   float m23 = det * - ( m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112 );
   float m30 = det * - ( m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123 );
   float m31 = det *   ( m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123 );
   float m32 = det * - ( m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113 );
   float m33 = det *   ( m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112 );

   return matrix(
        m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33
    );
}

// Matriz identidade.
glm::mat4 Matrices::identity()
{
    return matrix(
        1.0f , 0.0f , 0.0f , 0.0f , // LINHA 1
        0.0f , 1.0f , 0.0f , 0.0f , // LINHA 2
        0.0f , 0.0f , 1.0f , 0.0f , // LINHA 3
        0.0f , 0.0f , 0.0f , 1.0f   // LINHA 4
    );
}

// Matriz de translação T. Seja p=[px,py,pz,pw] um ponto e t=[tx,ty,tz,0] um
// vetor em coordenadas homogêneas, definidos em um sistema de coordenadas
// Cartesiano. Então, a matriz T é definida pela seguinte igualdade:
//
//     T*p = p+t.
//
glm::mat4 Matrices::translate(float tx, float ty, float tz)
{
    return matrix(
        1.0f , 0.0f , 0.0f , tx ,
        0.0f , 1.0f , 0.0f , ty ,
        0.0f , 0.0f , 1.0f , tz ,
        0.0f , 0.0f , 0.0f , 1.0f
    );
}

// Matriz S de "escalamento de um ponto" em relação à origem do sistema de
// coordenadas. Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz S é definida pela seguinte igualdade:
//
//     S*p = [sx*px, sy*py, sz*pz, pw].
//
glm::mat4 Matrices::scale(float sx, float sy, float sz)
{
    return matrix(
        sx   , 0.0f , 0.0f , 0.0f ,
        0.0f , sy   , 0.0f , 0.0f ,
        0.0f , 0.0f , sz   , 0.0f ,
        0.0f , 0.0f , 0.0f , 1.0f
    );
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo X (primeiro vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ px, c*py-s*pz, s*py+c*pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
glm::mat4 Matrices::rotate_x(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return matrix(
        1.0f , 0.0f , 0.0f , 0.0f ,
        0.0f ,  c   , -s   , 0.0f ,
        0.0f ,  s   ,  c   , 0.0f ,
        0.0f , 0.0f , 0.0f , 1.0f
    );
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo Y (segundo vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ c*px+s*pz, py, -s*px+c*pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
glm::mat4 Matrices::rotate_y(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return matrix(
         c   , 0.0f ,  s   , 0.0f ,
        0.0f , 1.0f , 0.0f , 0.0f ,
        -s   , 0.0f ,  c   , 0.0f ,
        0.0f , 0.0f , 0.0f , 1.0f
    );
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo Z (terceiro vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ c*px-s*py, s*px+c*py, pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
glm::mat4 Matrices::rotate_z(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return matrix(
         c   , -s   , 0.0f , 0.0f ,
         s   ,  c   , 0.0f , 0.0f ,
        0.0f , 0.0f , 1.0f , 0.0f ,
        0.0f , 0.0f , 0.0f , 1.0f
    );
}

// Função que calcula a norma Euclidiana de um vetor cujos coeficientes são
// definidos em uma base ortonormal qualquer.
float Matrices::norm(glm::vec4 v)
{
    float vx = v.x;
    float vy = v.y;
    float vz = v.z;

    return sqrt( vx*vx + vy*vy + vz*vz );
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo definido pelo vetor 'axis'. Esta matriz pode
// ser definida pela fórmula de Rodrigues. Lembre-se que o vetor que define o
// eixo de rotação deve ser normalizado!
glm::mat4 Matrices::rotate(float angle, glm::vec4 axis)
{
    float c = cos(angle);
    float s = sin(angle);

    glm::vec4 v = axis / norm(axis);

    float vx = v.x;
    float vy = v.y;
    float vz = v.z;

    return matrix(
        vx*vx*(1.0f-c)+c    , vx*vy*(1.0f-c)-vz*s , vx*vz*(1-c)+vy*s , 0.0f ,
        vx*vy*(1.0f-c)+vz*s , vy*vy*(1.0f-c)+c    , vy*vz*(1-c)-vx*s , 0.0f ,
        vx*vz*(1-c)-vy*s    , vy*vz*(1-c)+vx*s    , vz*vz*(1.0f-c)+c , 0.0f ,
        0.0f                , 0.0f                , 0.0f             , 1.0f
    );
}

// Produto vetorial entre dois vetores u e v definidos em um sistema de
// coordenadas ortonormal.
glm::vec4 Matrices::cross_product(glm::vec4 u, glm::vec4 v)
{
    float u1 = u.x;
    float u2 = u.y;
    float u3 = u.z;
    float v1 = v.x;
    float v2 = v.y;
    float v3 = v.z;

    return glm::vec4(
        u2*v3 - u3*v2, // Primeiro coeficiente
        u3*v1 - u1*v3, // Segundo coeficiente
        u1*v2 - u2*v1, // Terceiro coeficiente
        0.0f // w = 0 para vetores.
    );
}

// Produto escalar entre dois vetores u e v definidos em um sistema de
// coordenadas ortonormal.
float Matrices::dot_product(glm::vec4 u, glm::vec4 v)
{
    float u1 = u.x;
    float u2 = u.y;
    float u3 = u.z;
    float u4 = u.w;
    float v1 = v.x;
    float v2 = v.y;
    float v3 = v.z;
    float v4 = v.w;

    if ( u4 != 0.0f || v4 != 0.0f )
    {
        fprintf(stderr, "ERROR: Produto escalar não definido para pontos.\n");
        std::exit(EXIT_FAILURE);
    }

    return u1*v1 + u2*v2 + u3*v3;
}

// Matriz de mudança de coordenadas para o sistema de coordenadas da Câmera.
glm::mat4 Matrices::camera_view(glm::vec4 position_c, glm::vec4 view_vector, glm::vec4 up_vector)
{
    glm::vec4 w = -view_vector;
    glm::vec4 u = cross_product(up_vector, w);

    // Normalizamos os vetores u e w
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 v = cross_product(w,u);

    glm::vec4 origin_o = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    float ux = u.x;
    float uy = u.y;
    float uz = u.z;
    float vx = v.x;
    float vy = v.y;
    float vz = v.z;
    float wx = w.x;
    float wy = w.y;
    float wz = w.z;

    return matrix(
        ux   , uy   , uz   , -dot_product(u , position_c - origin_o) ,
        vx   , vy   , vz   , -dot_product(v , position_c - origin_o) ,
        wx   , wy   , wz   , -dot_product(w , position_c - origin_o) ,
        0.0f , 0.0f , 0.0f , 1.0f
    );
}

// Matriz de projeção paralela ortográfica
glm::mat4 Matrices::orthographic_view(float l, float r, float b, float t, float n, float f)
{
    glm::mat4 M = matrix(
        2.0f/(r-l) , 0.0f       , 0.0f       , -(r+l)/(r-l) ,
        0.0f       , 2.0f/(t-b) , 0.0f       , -(t+b)/(t-b) ,
        0.0f       , 0.0f       , 2.0f/(f-n) , -(f+n)/(f-n) ,
        0.0f       , 0.0f       , 0.0f       , 1.0f
    );

    return M;
}

// Matriz de projeção perspectiva
glm::mat4 Matrices::perspective_view(float field_of_view, float aspect, float n, float f)
{
    float t = fabs(n) * tanf(field_of_view / 2.0f);
    float b = -t;
    float r = t * aspect;
    float l = -r;

    glm::mat4 P = matrix(
        n    , 0.0f , 0.0f , 0.0f,
        0.0f , n    , 0.0f , 0.0f,
        0.0f , 0.0f , n+f  , -f*n,
        0.0f , 0.0f , 1.0f , 0.0f
    );

    // A matriz M é a mesma computada acima em orthographic_view().
    glm::mat4 M = orthographic_view(l, r, b, t, n, f);

    // Note que as matrizes M*P e -M*P fazem exatamente a mesma projeção
    // perspectiva, já que o sinal de negativo não irá afetar o resultado
    // devido à divisão por w. Por exemplo, seja q = [qx,qy,qz,1] um ponto:
    //
    //      M*P*q = [ qx', qy', qz', w ]
    //   =(div w)=> [ qx'/w, qy'/w, qz'/w, 1 ]   Eq. (*)
    //
    // agora com o sinal de negativo:
    //
    //     -M*P*q = [ -qx', -qy', -qz', -w ]
    //   =(div w)=> [ -qx'/-w, -qy'/-w, -qz'/-w, -w/-w ]
    //            = [ qx'/w, qy'/w, qz'/w, 1 ]   Eq. (**)
    //
    // Note que o ponto final, após divisão por w, é igual: Eq. (*) == Eq. (**).
    //
    // Então, por que utilizamos -M*P ao invés de M*P? Pois a especificação de
    // OpenGL define que os pontos fora do cubo unitário NDC deverão ser
    // descartados já que não irão aparecer na tela. O teste que define se um ponto
    // q está dentro do cubo unitário NDC pode ser expresso como:
    //
    //      -1 <= qx'/w <= 1   &&  -1 <= qy'/w <= 1   &&  -1 <= qz'/w <= 1
    //
    // ou, de maneira equivalente SE w > 0, a placa de vídeo faz o seguinte teste
    // ANTES da divisão por w:
    //
    //      -w <= qx' <= w   &&  -w <= qy' <= w   &&  -w <= qz' <= w
    //
    // Note que o teste acima economiza uma divisão por w caso o ponto seja
    // descartado (quando esteja fora de NDC), entretanto, este último teste só
    // é equivalente ao primeiro teste SE E SOMENTE SE w > 0 (isto é, se w for
    // positivo). Como este último teste é o que a placa de vídeo (GPU) irá fazer,
    // precisamos utilizar a matriz -M*P para projeção perspectiva, de forma que
    // w seja positivo.
    //
    return -M*P;
}

// Função que imprime uma matriz M no terminal
void Matrices::print_matrix(glm::mat4 M)
{
    printf("\n");
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ]\n", M[0][0], M[1][0], M[2][0], M[3][0]);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ]\n", M[0][1], M[1][1], M[2][1], M[3][1]);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ]\n", M[0][2], M[1][2], M[2][2], M[3][2]);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ]\n", M[0][3], M[1][3], M[2][3], M[3][3]);
}

// Função que imprime um vetor v no terminal
void Matrices::print_vector(glm::vec4 v)
{
    printf("\n");
    printf("[ %+0.2f ]\n", v[0]);
    printf("[ %+0.2f ]\n", v[1]);
    printf("[ %+0.2f ]\n", v[2]);
    printf("[ %+0.2f ]\n", v[3]);
}

// Função que imprime o produto de uma matriz por um vetor no terminal
void Matrices::print_matrix_vector_product(glm::mat4 M, glm::vec4 v)
{
    auto r = M*v;
    printf("\n");
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ]   [ %+0.2f ]\n", M[0][0], M[1][0], M[2][0], M[3][0], v[0], r[0]);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ] = [ %+0.2f ]\n", M[0][1], M[1][1], M[2][1], M[3][1], v[1], r[1]);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ]   [ %+0.2f ]\n", M[0][2], M[1][2], M[2][2], M[3][2], v[2], r[2]);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ]   [ %+0.2f ]\n", M[0][3], M[1][3], M[2][3], M[3][3], v[3], r[3]);
}

// Função que imprime o produto de uma matriz por um vetor, junto com divisão
// por w, no terminal.
void Matrices::print_matrix_vector_product_div_w(glm::mat4 M, glm::vec4 v)
{
    auto r = M*v;
    auto w = r[3];
    printf("\n");
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ]   [ %+0.2f ]            [ %+0.2f ]\n", M[0][0], M[1][0], M[2][0], M[3][0], v[0], r[0], r[0]/w);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ] = [ %+0.2f ] =(div w)=> [ %+0.2f ]\n", M[0][1], M[1][1], M[2][1], M[3][1], v[1], r[1], r[1]/w);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ]   [ %+0.2f ]            [ %+0.2f ]\n", M[0][2], M[1][2], M[2][2], M[3][2], v[2], r[2], r[2]/w);
    printf("[ %+0.2f  %+0.2f  %+0.2f  %+0.2f ][ %+0.2f ]   [ %+0.2f ]            [ %+0.2f ]\n", M[0][3], M[1][3], M[2][3], M[3][3], v[3], r[3], r[3]/w);
}

