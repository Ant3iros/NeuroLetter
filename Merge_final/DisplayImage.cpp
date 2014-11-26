#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "DisplayImage.hpp"
#include "opencv/highgui.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <SFML/Window/Input.hpp>

//#include "opencv/cv.h"


int main(int argc, char** argv )
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "My window");
  sf::Image image;
  sf::Sprite sprite;
  sf::Image image_ASCI;
  sf::Sprite sprite_ASCI;
  sf::Font MyFont;

  if ( argc != 2 )
    {
      printf("usage: DisplayImage.out <Image_Path>\n");
      return -1;
    }

  if (!image.LoadFromFile("../Background.bmp") || !image_ASCI.LoadFromFile(argv[1]))
    return(0);

  sprite.SetImage(image);
  sprite.Resize(600, 600);
  sprite_ASCI.SetImage(image_ASCI);
  sprite_ASCI.Resize(400, 400);

  while (window.IsOpened())
    {
      // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
      window.Clear();
      window.Draw(sprite);
      window.Draw(sprite_ASCI);
      window.Display();
      sf::Event event;
      
      while (window.GetEvent(event))
        {
          // évènement "fermeture demandée" : on ferme la fenêtre  
          if (event.Type == sf::Event::Closed)
            window.Close();
          if (event.Type == sf::Event::MouseButtonPressed)
            {
	      
              if ((window.GetInput().GetMouseX() <= 596 && window.GetInput().GetMouseX() >= 398) &&
                  (window.GetInput().GetMouseY() <= 474 && window.GetInput().GetMouseY() >= 439))
		{
		std::cout << "LAUNCH SUCCEES" <<  std::endl; 
		DisplayImage *display = new DisplayImage(argv[1]);// ICI faire appelle a la binarisation    
		// ICI faire appelle au reseau de NEURONE// ICI faire appelle au reseau de NEURONE
		}
	    }
        }
    }
  return 0;
}
