/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#include "moje.h"

namespace Models {
	
	Moje moje;
	
	Moje::Moje() {
		vertices=MojeInternal::vertices;
		normals=MojeInternal::normals;
		vertexNormals=MojeInternal::vertexNormals;
		texCoords=MojeInternal::texCoords;
		colors=MojeInternal::colors;
		vertexCount=MojeInternal::vertexCount;
	}
	
	Moje::~Moje() {
	}
	
	void Moje::drawSolid() {
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(4,GL_FLOAT,0,vertices);
		//glColorPointer(4,GL_FLOAT,0,colors);
		glNormalPointer(GL_FLOAT,sizeof(float)*4,vertexNormals);
		glTexCoordPointer(2,GL_FLOAT,0,texCoords);
		
		glDrawArrays(GL_TRIANGLES,0,vertexCount);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	
	
	namespace MojeInternal {
		
		unsigned int vertexCount=24;
		float vertices[]={
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f
		};
		float normals[]={
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f
		};
		float vertexNormals[]={
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			
			0.0f,-2.0f,0.0f,1.0f,
			0.0f, 0.0f,-1.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f
		};
		float texCoords[]={
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
				
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
				
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
				
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f
		};
		float colors[]={
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
		
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
		
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
		
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
		
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
		
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
		
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
		
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.2f, 1.0f
		};
	}
}