 #include <math.h>
 #include <scop_math.h>

float   ft_rad(float angle)
{
    return (angle * M_PI / 180);
}

void    ft_mat4_copy(t_mat4 src, t_mat4 dest)
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dest[i][j] = src[i][j];
            j++;
        }
        i++;
    }
}

void    ft_compute_rot(t_mat4 m, float cos, t_vec3 vs)
{
    m[0][0] += cos;
    m[0][1] += vs[2];
    m[0][2] -= vs[1];

    m[1][0] -= vs[2];
    m[1][1] += cos;
    m[1][2] += vs[0];

    m[2][0] += vs[1];
    m[2][1] -= vs[0];
    m[2][2] += cos;

    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void    ft_mul_rot_wrapped(t_mat4 m1, t_mat4 m2, t_mat4 dest)
{
    dest[0][0] = m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2];
    dest[0][1] = m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2];
    dest[0][2] = m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2];
    dest[0][3] = m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2];

    dest[1][0] = m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2];
    dest[1][1] = m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2];
    dest[1][2] = m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2];
    dest[1][3] = m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2];

    dest[2][0] = m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2];
    dest[2][1] = m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2];
    dest[2][2] = m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2];
    dest[2][3] = m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2];

    dest[3][0] = m1[3][0];
    dest[3][1] = m1[3][1];
    dest[3][2] = m1[3][2];
    dest[3][3] = m1[3][3];
}

void    ft_mul_rot(t_mat4 src, t_mat4 rot, t_mat4 dest)
{
    t_mat4  cpy;

    /*
    ** We copy m1 into another mat4, because mul_rot will overwrite m1 if m1==dest.
    */
    ft_mat4_copy(src, cpy);
    ft_mul_rot_wrapped(cpy, rot, dest);
}

void    ft_mat4_rotate(t_mat4 model, float angle, t_vec3 axis)
{
    t_mat4      rot;
    t_vec3      v;
    t_vec3      axis_new;
    t_vec3      vs;
    float       cos;

    /*
    ** Angle must be in rads !
    */
    cos = cosf(angle);

    ft_vec3_normalize_to(axis, axis_new);
    ft_vec3_scale(axis_new, 1.0f - cos, v);
    ft_vec3_scale(axis_new, sinf(angle), vs);

    ft_vec3_scale(axis_new, v[0], rot[0]);
    ft_vec3_scale(axis_new, v[1], rot[1]);
    ft_vec3_scale(axis_new, v[2], rot[2]);

    ft_compute_rot(rot, cos, vs);
    ft_mul_rot(model, rot, model);
}
