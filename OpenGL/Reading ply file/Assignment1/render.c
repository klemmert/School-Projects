#include "stdlib.h"
#include "GL/glut.h"
#include "math.h"
#include "ply.h"

void read_test();

/* polygon description of an object (a cube) */

Vertex verts[] = {  /* vertices */
  { 0.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0},
  { 1.0, 1.0, 0.0},
  { 0.0, 1.0, 0.0},
  { 0.0, 0.0, 1.0},
  { 1.0, 0.0, 1.0},
  { 1.0, 1.0, 1.0},
  { 0.0, 1.0, 1.0},
};

Face faces[] = {  /* faces */
  { '\001', 4, NULL },  /* intensity, vertex list count, vertex list (empty) */
  { '\004', 4, NULL },
  { '\010', 4, NULL },
  { '\020', 4, NULL },
  { '\144', 4, NULL },
  { '\377', 4, NULL },
};

/* list of vertices for each face */
/* (notice that indices begin at zero) */

typedef int Vertex_Indices[4];
Vertex_Indices vert_ptrs[] = {
  { 0, 1, 2, 3 },
  { 7, 6, 5, 4 },
  { 0, 4, 5, 1 },
  { 1, 5, 6, 2 },
  { 2, 6, 7, 3 },
  { 3, 7, 4, 0 },
};

/* Macro for checking OpenGL error state */

#define GLERROR                                                    \
    {                                                              \
        GLenum code = glGetError();                                \
        while (code!=GL_NO_ERROR)                                  \
        {                                                          \
            printf("%s\n",(char *) gluErrorString(code));          \
                code = glGetError();                               \
        }                                                          \
    }

int num_elems;
int vertexcount;
int facecount;
Vertex **vlist;
Face **flist;
int HEIGHT = 900;
int WIDTH = 1300;


/******************************************************************************
Read in a PLY file.
******************************************************************************/

void read_test()
{
	int i, j, k;
	PlyFile *ply;
	int nelems;
	char **elist;
	int file_type;
	float version;
	int nprops;
	PlyProperty **plist;
	char *elem_name;
	int num_comments;
	char **comments;
	int num_obj_info;
	char **obj_info;

	/* open a PLY file for reading */
	ply = ply_open_for_reading("hand", &nelems, &elist, &file_type, &version);

	/* print what we found out about the file */
	//printf("version %f\n", version);
	//printf("type %d\n", file_type);

	/* go through each kind of element that we learned is in the file */
	/* and read them */

	for (i = 0; i < nelems; i++) {

		/* get the description of the first element */
		elem_name = elist[i];
		plist = ply_get_element_description(ply, elem_name, &num_elems, &nprops);

		/* print the name of the element, for debugging */
		//printf("element %s %d\n", elem_name, num_elems);

		/* if we're on vertex elements, read them in */
		if (equal_strings("vertex", elem_name)) {

			/* create a vertex list to hold all the vertices */
			vlist = (Vertex **)malloc(sizeof(Vertex *) * num_elems);

			/* set up for getting vertex elements */

			ply_get_property(ply, elem_name, &vert_props[0]);
			ply_get_property(ply, elem_name, &vert_props[1]);
			ply_get_property(ply, elem_name, &vert_props[2]);

			/* grab all the vertex elements */
			for (j = 0; j < num_elems; j++) {

				/* grab and element from the file */
				vlist[j] = (Vertex *)malloc(sizeof(Vertex));
				ply_get_element(ply, (void *)vlist[j]);

				/* print out vertex x,y,z for debugging */
				//printf("vertex: %g %g %g\n", vlist[j]->x, vlist[j]->y, vlist[j]->z);
				vertexcount++;
			}
		}

		/* if we're on face elements, read them in */
		if (equal_strings("face", elem_name)) {

			/* create a list to hold all the face elements */
			flist = (Face **)malloc(sizeof(Face *) * num_elems);

			/* set up for getting face elements */

			ply_get_property(ply, elem_name, &face_props[0]);
			ply_get_property(ply, elem_name, &face_props[1]);

			/* grab all the face elements */
			for (j = 0; j < num_elems; j++) {

				/* grab and element from the file */
				flist[j] = (Face *)malloc(sizeof(Face));
				ply_get_element(ply, (void *)flist[j]);

				/* print out face info, for debugging */
				//printf("face: %d, list = ", flist[j]->intensity);
				//for (k = 0; k < flist[j]->nverts; k++)
					//printf("%d ", flist[j]->verts[k]);
				//printf("\n");
				facecount++;
			}
		}

		/* print out the properties we got, for debugging */
		//for (j = 0; j < nprops; j++)
			//printf("property %s\n", plist[j]->name);
	}

	/* grab and print out the comments in the file */
	//comments = ply_get_comments(ply, &num_comments);
	//for (i = 0; i < num_comments; i++)
		//printf("comment = '%s'\n", comments[i]);

	/* grab and print out the object information */
	//obj_info = ply_get_obj_info(ply, &num_obj_info);
	//for (i = 0; i < num_obj_info; i++)
		//printf("obj_info = '%s'\n", obj_info[i]);

	/* close the PLY file */
	ply_close(ply);
}

void init() 
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	
	glViewport(0, HEIGHT / 2, WIDTH / 2, HEIGHT / 2); //top view
	glLoadIdentity();
	gluLookAt(0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -5.0);
	drawObj();
	glViewport(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2); //side view
	glLoadIdentity();
	gluLookAt(-15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	drawObj();
	glViewport(0, 0, WIDTH / 2, HEIGHT / 2); //front view
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	drawObj();
	

	glFlush();
}

drawObj() {

	for (int i = 0; i < facecount - 1; i++) {
		glColor3f(0.0, 0.0, 0.0 + (i / 10)); //make it blue
		glBegin(GL_POLYGON);
		for (int j = 0; j < flist[i]->nverts; j++) {
			glVertex3f(vlist[flist[i]->verts[j]]->x, vlist[flist[i]->verts[j]]->y, vlist[flist[i]->verts[j]]->z);
		}
		glEnd();
	}
}

static void reshape() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) 
{
	//read in the ply file
	read_test();

	//make window and display (from powerpoint slides)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("title bar");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}