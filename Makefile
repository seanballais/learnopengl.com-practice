1-getting-started:
	g++ -g -I include/ \
    	-o src/1-getting-started/getting-started \
    	src/1-getting-started/getting-started.cpp src/utils/glad.c \
    	-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl; \
    chmod +x src/1-getting-started/getting-started
