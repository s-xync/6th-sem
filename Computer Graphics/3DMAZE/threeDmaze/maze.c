// https://en.wikipedia.org/wiki/Maze_generation_algorithm#Simple_algorithms
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct{
	int x, y;
	void *parent;
	char c;
	char dirs;
} Node;
Node *nodes;
int width,height;
int twodmazearray[200][200];
int init(){
	int i, j;
	Node *n;
	nodes = calloc( width * height, sizeof( Node ) );
	if ( nodes == NULL ) return 1;
	for ( i = 0; i < width; i++ ){
		for ( j = 0; j < height; j++ ){
			n = nodes + i + j * width;
			if ( i * j % 2 ){
				n->x = i;
				n->y = j;
				n->dirs = 15;
				n->c = ' '; 
			}
			else n->c = '#';
		}
	}
	return 0;
}

Node *link(Node *n){
	int x,y;
	char dir;
	Node *dest;
	if (n==NULL) return NULL;
	while (n->dirs){
		dir=(1<<(rand()%4));
		if (~n->dirs&dir) continue;
		n->dirs &= ~dir;
		switch (dir){
			case 1:
				if (n->x+2<width){
					x=n->x+2;
					y=n->y;
				}
				else continue;
				break;
			case 2:
				if (n->y+2<height){
					x=n->x;
					y=n->y+2;
				}
				else continue;
				break;
			case 4:
				if (n->x-2>=0){
					x = n->x - 2;
					y = n->y;
				}
				else continue;
				break;
			case 8:
				if (n->y-2>=0){
					x = n->x;
					y = n->y - 2;
				}
				else continue;
				break;
		}
		dest = nodes + x + y * width;
		if ( dest->c == ' ' ){
			if ( dest->parent != NULL ) continue;
			dest->parent = n;
			nodes[n->x + ( x - n->x ) / 2 + ( n->y + ( y - n->y ) / 2 ) * width].c = ' ';
			return dest;
		}
	}
	return n->parent;
}

void draw(){
	int i,j;
	for (i = 0;i<height;i++){
		for (j=0;j<width;j++){
			printf("%c",nodes[j+i*width].c);
			if(nodes[j+i*width].c=='#'){
				twodmazearray[i][j]=1;
			}
		}
		printf( "\n" );
	}
}

void drawArray(){
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			printf("%d",twodmazearray[i][j]);
		}
		printf("\n");
	}
}

int main( int argc, char **argv ){
	Node *start, *last;
	if ( argc < 3 ){
		fprintf( stderr, "%s: please specify maze dimensions!\n", argv[0] );
		exit(1);
	}
	if ( sscanf( argv[1], "%d", &width ) + sscanf( argv[2], "%d", &height ) < 2 ){
		fprintf( stderr, "%s: invalid maze size value!\n", argv[0] );
		exit( 1 );
	}
	if ( !( width % 2 ) || !( height % 2 ) ){
		fprintf( stderr, "%s: dimensions must be odd!\n", argv[0] );
		exit( 1 );
	}
	if ( width <= 0 || height <= 0 ){
		fprintf( stderr, "%s: dimensions must be greater than 0!\n", argv[0] );
		exit( 1 );
	}
	srand( time( NULL ) );
	if (init()){
		fprintf( stderr, "%s: out of memory!\n", argv[0] );
		exit( 1 );
	}
	start = nodes + 1 + width;
	start->parent = start;
	last = start;
	while ( ( last = link( last ) ) != start );
	for(int i=0;i<200;i++){
		for(int j=0;j<200;j++){
			twodmazearray[i][j]=0;
		}
	}
	printf("Maze\n");
	draw();
	printf("\n");
	printf("Maze Array\n");
	drawArray();
}

// for(i=0; i<width; i++){
//     for(j=0; j<height; j++){
//         if(maze[i][j] == 1){  // Means there is a cube there
//             glPushMatrix();
//             glTranslatef(j * scale, 0, i * scale);
//             DrawCube();
//             glPopMatrix();
//         }
//     }
// }