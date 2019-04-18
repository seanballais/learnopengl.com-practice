all: 1-getting-started 1-getting-started-exer-hello-triangle-1

1-getting-started:
	g++ -g -I include/ \
    	-o src/1-getting-started/getting-started \
    	src/1-getting-started/getting-started.cpp src/utils/glad.c \
    	-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl; \
    chmod +x src/1-getting-started/getting-started

1-getting-started-exer-hello-triangle-1:
	g++ -g -I include/ \
    	-o src/1-getting-started/exer-hello-triangle-1 \
    	src/1-getting-started/exer-hello-triangle-1.cpp src/utils/glad.c \
    	-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl; \
    chmod +x src/1-getting-started/exer-hello-triangle-1
