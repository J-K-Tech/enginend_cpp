#pragma once
#define GAME_GRAPHICS 1
#include<enginend.h>
extern bool accelerated;
class Window;


typedef struct color {
	unsigned char r,g,b,a;
};
extern color clearcolor;
typedef struct buffer{
	short width,height;
	char mode;
	color*data;
	buffer(int width, int height, char mode):width(width),height(height),mode(mode),data(
		 (color*)malloc(width * height * sizeof(color))
	){for (int i = 0; i < width * height; i++){
		data[i] = {clearcolor.r,clearcolor.g,clearcolor.b,clearcolor.a};
	}};
	buffer():width(0),height(0),mode(0),data(0){};
	~buffer(){free(data);};
	void clear(){for (int i = 0; i < width * height; i++){
		data[i] = {clearcolor.r,clearcolor.g,clearcolor.b,clearcolor.a};
		}};
	
};

class Object{
public:
	int UUID;
	virtual void render(Window* window)=0;
	static void draw(Object* self,Window* window) {self->render(window);}
	Object** children;
};

#if GAME_GRAPHICS >=0
class Object2D: public Object{
	public:
		short x, y;	short roll;
		buffer pixelbuffer;
		Object2D(){};
		Object2D(short x, short y):x(x),y(y),pixelbuffer(x,y,0){};
		void render(Window* window) {}
};
class World:public Object2D{
public:
	color fog;
	Object2D camera;
	Object2D* stuff;

	World(){};
	void render(Window* window) override;
};
	#if GAME_GRAPHICS >=1
struct Camera {
	vec3 position;
	vec3 rotation;
	short fov;
	short aspect;
	short nearClip;
	short farClip;
	Camera() {}
	Camera(vec3 pos, vec3 rot, short fov, short aspect, short nearClip = 0.1f, short farClip = 1000.0f)
		: position(pos), rotation(rot), fov(fov), aspect(aspect), nearClip(nearClip), farClip(farClip) {}
	mat4 getviewmatrix() {
		mat4 rot= mat4::rotation(rotation.x, rotation.y, rotation.z);
		mat4 trans= mat4::translation(-position.x, -position.y, -position.z);
		return trans * rot;
	}
	};
	class Object3D: public Object2D{
		public:
			short z;	short pitch, yaw;
			Object3D(){};
			Object3D(short x, short y,short z):Object2D(x,y){this->z = z;};
			void render(Window* window) {}
	};
	struct Triangle{
		//index
		int v0,v1,v2;
		vec3 normal;
		Triangle(int v0, int v1, int v2):v0(v0),v1(v1),v2(v2){};
	};

	class model:public Object3D{
		public:
			vec3* vertices;
			Triangle *faces;
			void render(Window* window) {}
			model(){};
			model(vec3* vertices, Triangle* faces):vertices(vertices),faces(faces){};
			~model(){free(vertices);free(faces);};
	};
	class World3D:public Object3D{
	public:
		color fog;
		Camera camera;
		model* stuff;

		World3D(){};
		void render(Window* window) override;
	};
	#endif
#endif

class Window {
	public:

		bool running = true;
		key keys;
		mousee mouse;
		void (**drawfuncs)(Object*,Window*)=nullptr;
		Object** objects=nullptr;
		int draws = 0;
		windowtype window; renderertype renderer;
		SDL_Event event;
		Window(int width, int height, const char* title);
		~Window();
		bool eventupdate();
		bool pressed(int key);
		bool changed(int key);
		void update();
		void bind(void (*func)(Object*,Window*), Object* obj);
		texturetype framebuffer;

};