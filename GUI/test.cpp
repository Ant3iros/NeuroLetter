#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <SFML/Window/Input.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "My window");

  // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
  
  sf::Image image;
  sf::Sprite sprite;
  sf::Image image_ASCI;
  sf::Sprite sprite_ASCI;
  sf::Font MyFont;
  
  if (!image.LoadFromFile("../Background.bmp") || !image_ASCI.LoadFromFile("../a.bmp"))
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
	      std::cout << "X = "<< window.GetInput().GetMouseX() << " Y = " << window.GetInput().GetMouseY() << std::endl;
	      if ((window.GetInput().GetMouseX() <= 596 && window.GetInput().GetMouseX() >= 398) &&
		  (window.GetInput().GetMouseY() <= 474 && window.GetInput().GetMouseY() >= 439))
		std::cout << "LAUNCH SUCCEES" <<  std::endl; // ICI faire appelle au reseau de NEURONE
	    }
        }
    }
 return 0;
}
