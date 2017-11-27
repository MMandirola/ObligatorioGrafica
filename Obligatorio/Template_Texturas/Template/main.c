#include "framework/canvas.h"
#include "framework/mm.h"

#ifdef WIN32
#include "glew.h"
#else
#include <GL/gl.h>
#endif

#include "objects/animation.h"
#include "shader.h"
#include <time.h>
#include <SDL/SDL_image.h>
#include "objects/obj.h"
#include "objects/element.h"
#include "math.h"
int main(int argc, char* argv[])
{
    // Crear una ventana de 500x500 pixels:
	int cw = 900;
	int ch = 900;

	cg_init(cw, ch, NULL);

#ifdef WIN32
    freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );

	GLenum err= glewInit();
	if(err!=GLEW_OK)
	{
		//problem: glewInit failed, something is seriously wrong
		printf("GLEW Error: %s\n", glewGetErrorString(err));
		return -1;
	}
#endif
    printf("GL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    glClearColor(0,0,1,1);
    // Actualizar la pantalla:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glMatrixMode(GL_PROJECTION);
    glViewport(0,0,cw, ch);
    glFrustum(-1,1,-1,1,1,1000);

    glEnable(GL_LIGHTING);

    // glEnable(GL_NORMALIZE);
    float l0[] = {2.0f,2.0f,2.0f,2.0f};
    // float l0[] = {1.0f,1.0f,1.0f,1.0f};
    float la[] = {0.10f,0.10f,0.10f,1.0f};
    float l0p[]= {1.0f,1.0f,1.0f,1.0f};
    // float ls[] = {1.0f,1.0f,1.0f,1.0f};
    float ls[] = {2.0f,2.0f,2.0f,2.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, la);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l0);
    glLightfv(GL_LIGHT0, GL_POSITION, l0p);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ls);
    glEnable(GL_LIGHT0);

    float cyan[] = {1.0f, 1.0f, 1.0f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ls);
    glMateriali(GL_FRONT, GL_SHININESS, 16);

    float ang = 0.0f;
    float pitch = 0.0f;
    float model_pitch = 0.0f;
    float model_ang = 0.0f;
    float x_coord = 0.0f;
    float y_coord = 0.0f;
    float z_coord = 0.0f;
    float zoom = 1.0f;
    float zoom_vel = 0.1f;
    float distance_vel = 2.0f;
    float ang_vel = 1.0f;

    Animation  animation;
    Animation  animation2;
    Animation * anim = &animation;
    Animation * anim2 = &animation2;
    // Obj* box = malloc(sizeof(Obj));
    ArrayList * animations = malloc(sizeof(ArrayList));
    ArrayList * parsed_objs = malloc(sizeof(ArrayList));
    initArrayList(sizeof(Obj), parsed_objs);
    initArrayList(sizeof(Animation), animations);
    // printf("%s\n", "inst list");
    char * objs[] = {"Models/knight_run_0.obj","Models/knight_run_1.obj","Models/knight_run_2.obj", "Models/knight_run_3.obj", "Models/knight_run_4.obj", "Models/knight_run_5.obj", "Models/knight_pain_a_0.obj", "Models/knight_pain_a_1.obj", "Models/knight_pain_a_2.obj", "Models/knight_pain_a_3.obj"};
    for ( int i = 0; i < 10; i++){
        Obj obj;
        initObj(&obj);
        parseObj(objs[i], &obj);
        prepareToDraw(&obj);
        addElement(&obj, parsed_objs);
    }
    // printf("%s\n", "loaded");
    int indexes1[] = {0,1,2,3,4,5};
    int indexes2[] = {6,7,8,9};
    int animindexes[] = {0};
    int animindexes2[] = {1};
    int animindexes3[] = {0};
    initAnimation(anim, indexes1, parsed_objs->vector, 6, 0.5f);
    initAnimation(anim2, indexes2, parsed_objs->vector, 4, 1.0f);
    addElement(anim, animations);
    addElement(anim2, animations);
    Element * elem1 = malloc(sizeof(Element)); 
    Element * elem2 = malloc(sizeof(Element));
    Element * elem3 = malloc(sizeof(Element));
    Element * root =  malloc(sizeof(Element));


    // parseObj("knight_texturas.obj", box);
    // prepareToDraw(box);
    // Obj* box = obj_load("Models/knight_texturas.obj");
	char done = 0;
	char wireframe = 0;
	char bfc = 0;
	glEnable(GL_DEPTH_TEST);
	char zbuff = 1;
    unsigned char key_pressed[1024];
    memset(key_pressed, 0, 1024);

    char use_shader = 0;
    char specular = 0;
    Shader gouraud = shader_new("shaders/gouraud_vp.glsl", "shaders/gouraud_fp.glsl");
    GLint uniform_especular = shader_get_unif_loc(gouraud, "especular");
    GLint uniform_tex = shader_get_unif_loc(gouraud, "tex");

    //Cargo la imagen de disco usando SDL_image
    SDL_Surface* surface = IMG_Load("Models/knight_good.png");
    if (surface==NULL) { //Si falla la carga de la imagen, despliego el mensaje de error correspondiente y termino el programa.
        printf("Error: \"%s\"\n",SDL_GetError());
        return 1;
    }

    GLuint texture[2];
    //Creo un espacio para alojar una textura en memoria de video
    glGenTextures(2,&texture);
    //Activo la textura nro 0
    glActiveTexture(GL_TEXTURE0);
    //Habilito la carga para la textura recien creada
    glBindTexture(GL_TEXTURE_2D,texture[0]);

    //Cargo los datos de la imagen en la textura.
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 surface->w,
                 surface->h,
                 0,
                 GL_RGB,GL_UNSIGNED_BYTE,
                 surface->pixels);
    //Luego de copiada la imagen a memoria de video, puedo liberarla sin problemas
    SDL_FreeSurface(surface);

    //Seteo el filtro a usar cuando se mapea la textura a una superficie mas chica (GL_LINEAR = filtro bilineal)
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    //Seteo el filtro a usar cuando se mapea la textura a una superficie mas grande (GL_LINEAR = filtro bilineal)
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    //Seteo el comportamiento cuando encuentro coordenadas de textura fuera del rango [0,1]
    //GL_REPEAT es el comportamiento por defecto.
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_REPEAT);

    surface = IMG_Load("Models/knight.png");
    glBindTexture(GL_TEXTURE_2D,texture[1]);

    //Cargo los datos de la imagen en la textura.
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 surface->w,
                 surface->h,
                 0,
                 GL_RGB,GL_UNSIGNED_BYTE,
                 surface->pixels);
    //Luego de copiada la imagen a memoria de video, puedo liberarla sin problemas
    SDL_FreeSurface(surface);

    //Seteo el filtro a usar cuando se mapea la textura a una superficie mas chica (GL_LINEAR = filtro bilineal)
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    //Seteo el filtro a usar cuando se mapea la textura a una superficie mas grande (GL_LINEAR = filtro bilineal)
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    //Seteo el comportamiento cuando encuentro coordenadas de textura fuera del rango [0,1]
    //GL_REPEAT es el comportamiento por defecto.
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_REPEAT);
    initElement(root, animations->vector, animindexes, 0, texture[0],0, 0, 0, 0,0,0, 1,1,1);
    initElement(elem1, animations->vector, animindexes, 1, texture[0],0.5, 0, 0, 0,0,0, 2,2,2);
    initElement(elem2, animations->vector, animindexes2, 1, texture[1], 0,0,0,0,0,-50.0f,1,1,1) ;
    initElement(elem3, animations->vector, animindexes3, 1, texture[1],0,0,0,0,0,50.0f,1,1,1); 
    addChild(root, elem1);
    addChild(elem1, elem3);
    addChild(root, elem2);


	while (!done)
	{

		SDL_Event event;
        float seconds = SDL_GetTicks() / (float) 1000;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
                    key_pressed[event.key.keysym.sym] = 1;
                    if (event.key.keysym.sym == SDLK_p)
				    {
				        use_shader = !use_shader;
				        break;
				    }
				    else if (event.key.keysym.sym == SDLK_x)
				    {
				        specular = !specular;
				        break;
				    }
                    else if (event.key.keysym.sym == SDLK_z)
				    {
				        zbuff = !zbuff;
				        if(zbuff)
                            glEnable(GL_DEPTH_TEST);
                        else
                            glDisable(GL_DEPTH_TEST);
				        break;
				    }
				    else if (event.key.keysym.sym == SDLK_m)
				    {
				        wireframe = !wireframe;
				        if(wireframe)
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        else
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				        break;
				    }
				    else if (event.key.keysym.sym == SDLK_b)
				    {
				        bfc = !bfc;
				        if(bfc)
				        {
                            glEnable(GL_CULL_FACE);
                            glCullFace(GL_BACK);
                            glFrontFace(GL_CW);
				        }
                        else
                            glDisable(GL_CULL_FACE);
				        break;
				    }
					else if (event.key.keysym.sym != SDLK_ESCAPE)
						break;
				case SDL_QUIT : done = 1;break;
				case SDL_KEYUP: key_pressed[event.key.keysym.sym] = 0;

			}
		}

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(ang, 0.0f, 1.0f, 0.0f);
        glTranslatef(x_coord, y_coord, z_coord);
        glScalef(zoom,zoom,zoom);
        glTranslatef(0.0f, 0.0f, -80.0f);
        glRotatef(model_pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(model_ang, 0.0f, 1.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        float r_ang = ang * 3.14159f / 180;
        float r_pitch = pitch * 3.14159f / 180;
        if(key_pressed[SDLK_RIGHT]) ang += ang_vel;
        if(key_pressed[SDLK_LEFT]) ang -= ang_vel;
        if(key_pressed[SDLK_UP]) pitch -= ang_vel;
        if(key_pressed[SDLK_DOWN]) pitch += ang_vel;

        if(key_pressed[SDLK_q]) y_coord += distance_vel;
        if(key_pressed[SDLK_e]) y_coord -= distance_vel;
        if(key_pressed[SDLK_a]){
            z_coord += cos(r_pitch) * cos(r_ang - (3.14159/2)) * distance_vel;
            x_coord += cos(r_pitch) * -sin(r_ang - (3.14159/2)) * distance_vel;
        }
        if(key_pressed[SDLK_d]){
            z_coord += cos(r_pitch) * cos(r_ang + (3.14159/2)) * distance_vel;
            x_coord += cos(r_pitch) * -sin(r_ang + (3.14159/2)) * distance_vel;

        }
        if(key_pressed[SDLK_w]){
            z_coord += cos(r_pitch) * cos(r_ang) * distance_vel;
            x_coord += cos(r_pitch) * -sin(r_ang) * distance_vel;
            y_coord += sin(r_pitch) * distance_vel;
        } 
        if(key_pressed[SDLK_s]){
            z_coord -= cos(r_pitch) * cos(r_ang) * distance_vel;
            x_coord -= cos(r_pitch) * -sin(r_ang) * distance_vel;
            y_coord -= sin(r_pitch) * distance_vel;
        } 
        if(key_pressed[SDLK_h]) model_ang += ang_vel;
        if(key_pressed[SDLK_j]) model_ang -= ang_vel;
        if(key_pressed[SDLK_k]) model_pitch -= ang_vel;
        if(key_pressed[SDLK_l]) model_pitch += ang_vel;
        if(key_pressed[SDLK_t]) zoom += zoom_vel;
        if(key_pressed[SDLK_y]){
            if (zoom - zoom_vel >= 0){
                zoom -= zoom_vel; 
            }
        }
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //Informo a OpenGL que para todas las operaciones a continuación utilice las texturas 2D cargadas
        glEnable(GL_TEXTURE_2D);

        if(use_shader)
        {
            shader_use(gouraud);
            glUniform1i(uniform_especular, specular);
            //Le digo al shader que el sampler2D de nombre "tex" se corresponde con GL_TEXTURE0
            //que es donde cargué mi textura.
            glUniform1i(uniform_tex, 0);
            //Luego asocio la textura con el id "texture"

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            renderElement(root, seconds);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            shader_stop(gouraud);
        }
        else
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            renderElement(root, seconds);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        cg_repaint();
	}
    for(int i = 0; i< parsed_objs->list_size; i++){
     Obj * obj= (Obj *) (parsed_objs->vector);
     freeObj(obj + i);
    }
    freeList(parsed_objs);
    for(int i = 0; i< animations->list_size; i++){
     Animation * animation = (Animation *) (animations->vector);
     freeAnimation(animation + i);
    }
    freeList(animations);
    freeElement(elem1);
    freeElement(elem2);
    freeElement(elem3);
    freeElement(root);
    shader_free(gouraud);
    glDeleteTextures(2,&texture);
	// Liberar recursos:
	cg_close();

	// Ejemplo del modulo de Manejo de Memoria (MM):
	int* pint = (int *)cg_malloc(10*sizeof(int));
	cg_free(pint); // olvidarse de liberar este objeto produce un mensaje


	return 0;
}
