#include <SDL_image.h>
#include <SDL.h>
#include <string>
class GUIElement
{
public:
	GUIElement()
	{

	}
	GUIElement(const std::string& t_path,float t_x,float t_y
	, float t_width, float t_height) :
		m_path(t_path),
		m_positionX(t_x),
		m_positionY(t_y),
		m_width(t_width),
		m_height(t_height)
	{

	}
	~GUIElement()
	{
		SDL_DestroyTexture(m_texture);
	}
	void render(SDL_Renderer* t_renderer)
	{
		m_destination.x = m_positionX;
		m_destination.y = m_positionY;
		m_destination.w = m_width;
		m_destination.h = m_height;
		SDL_RenderCopy(t_renderer, m_texture, NULL, &m_destination);
	}
	float m_positionX, m_positionY,m_width,m_height;
	std::string m_path;
protected:
private:
	SDL_Rect m_destination;
	SDL_Texture* m_texture;
};