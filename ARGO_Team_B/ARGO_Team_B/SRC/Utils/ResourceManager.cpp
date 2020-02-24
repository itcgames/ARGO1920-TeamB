//#include "ResourceManager.h"
//
//ResourceManager* ResourceManager::g_resourceManager = NULL;
//
//// getInstance()
//ResourceManager* ResourceManager::getInstance() {
//	if (!g_resourceManager)
//		g_resourceManager = new ResourceManager();
//	return g_resourceManager;
//}
//
//// Default Constructor
//ResourceManager::ResourceManager() {
//	// Do nothing
//}
//
//// Default Destructor
//ResourceManager::~ResourceManager() {
//	// Do nothing
//}
//
//// Load LTexture resource
//bool ResourceManager::loadTextureResource(SDL_Renderer* renderer, const char* path, std::string key_name) {
//	LTexture* gImage = new LTexture();
//	if (textureResource[key_name] == NULL) {
//		if (!gImage->loadFromFile(path, renderer)) {
//			SDL_Log("Unable to load Image!\n");
//			return false;
//		}
//		else {
//			textureResource[key_name] = gImage;
//		}
//	}
//	return true;
//}
//
//// Load Ture Type Font resource
//bool ResourceManager::loadTureTypeFontResource(SDL_Renderer* renderer, const char* path, int size, std::string key_name) {
//	if (TTF_Init() == -1)
//	{
//		if (fontResource[key_name] == NULL) {
//			gFont = TTF_OpenFont(path, size);
//			if (gFont == NULL) {
//				SDL_Log("Failed to open font!\n");
//				return false;
//			}
//			else
//				fontResource[key_name] = gFont;
//		}
//	}
//	
//	return true;
//}
//
//// Load Music resource
//bool ResourceManager::loadMixMusicResource(const char* path, std::string key_name) {
//	if (musicResource[key_name] == NULL) {
//		gMusic = Mix_LoadMUS(path);
//		if (gMusic == NULL) {
//			SDL_Log("Failed to open music!\n");
//			return false;
//		}
//		else
//			musicResource[key_name] = gMusic;
//	}
//	return true;
//}
//
//// Load Chunk resource
//bool ResourceManager::loadChunkResource(const char* path, std::string key_name) {
//	if (chunkResource[key_name] == NULL) {
//		gSound = Mix_LoadWAV(path);
//		if (gSound == NULL) {
//			SDL_Log("Failed to open chunk!\n");
//			return false;
//		}
//		else
//			chunkResource[key_name] = gSound;
//	}
//	return true;
//}
//
//
//
//bool ResourceManager::init() {
//	// Now do nothing
//	bool success = true;
//	return success;
//}
//
//// init
//bool ResourceManager::init(SDL_Renderer* renderer) {
//
//
//
//
//
//	// load textures.
//
//	bool texture_load_success =
//		loadTextureResource(renderer, "./Assets/Menu/backgroundImage.png", "backgroundImage") &&
//		loadTextureResource(renderer, "./Assets/Menu/botPlay.png", "botPlay") &&
//		loadTextureResource(renderer, "./Assets/Menu/credits.png", "credits") &&
//		loadTextureResource(renderer, "./Assets/Menu/localPlay.png", "localPlay") &&
//		loadTextureResource(renderer, "./Assets/Menu/onlinePlay.png", "onlinePlay") &&
//		loadTextureResource(renderer, "./Assets/Menu/quitGame.png", "quitGame");
//
//	if (!texture_load_success) printf("texture loading error.\n");
//
//	//load fonts.
//	bool font_load_success = 
//		loadTureTypeFontResource(renderer, "Assets/Fonts/Jungle Land.ttf", 30, "mainFont");
//
//	if (!font_load_success) printf("font loading error.\n");
//
//	//load music.
//	bool music_load_success = 
//		loadMixMusicResource("Assets/music/kungfu.mp3", "kungfu_background");
//
//	if (!music_load_success) printf("music loading error.\n");
//
//	// load sound effects.
//	bool sound_load_success = 
//		loadChunkResource("Assets/sound/passSound.wav", "pass_sound");
//
//	if (!sound_load_success) printf("sound loading error.\n");
//
//	std::cout << "ResourceManager Init ! \n";
//
//	// return texture_load_success && font_load_success && music_load_success && sound_load_success;
//	return texture_load_success;
//}
//
//
//// getters.
//LTexture* ResourceManager::getTextureResource(std::string key_name) {
//	return textureResource[key_name];
//}
//
//TTF_Font* ResourceManager::getTureTypeFontResource(std::string key_name) {
//	return fontResource[key_name];
//}
//
//Mix_Music* ResourceManager::getMixMusicResource(std::string key_name) {
//	return musicResource[key_name];
//}
//
//Mix_Chunk* ResourceManager::getChunkResource(std::string key_name) {
//	return chunkResource[key_name];
//}
//
//
//// update
//void ResourceManager::update() {
//	// Now do nothing
//}
//
//
//// quit
//bool ResourceManager::quit() {
//	// In quit, we destroy SDL_Surface* and all the textures and music resources
//	bool success = true;
//	// Free gFont
//	TTF_CloseFont(gFont);
//	gFont = NULL;
//	// Free gMusic
//	Mix_FreeMusic(gMusic);
//	gMusic = NULL;
//	// Free gChunk
//	Mix_FreeChunk(gSound);
//	gSound = NULL;
//
//	// Free textureResource
//	for (std::map<std::string, LTexture*>::iterator it = textureResource.begin();
//		it != textureResource.end();
//		it++)
//	{
//		it->second->free();
//	}
//
//	// Free fontResource
//	for (std::map<std::string, TTF_Font*>::iterator it = fontResource.begin();
//		it != fontResource.end();
//		it++)
//	{
//		TTF_CloseFont(it->second);
//	}
//
//	// Free musicResource
//	for (std::map<std::string, Mix_Music*>::iterator it = musicResource.begin();
//		it != musicResource.end();
//		it++)
//	{
//		Mix_FreeMusic(it->second);
//	}
//
//	// Free chunkResource
//	for (std::map<std::string, Mix_Chunk*>::iterator it = chunkResource.begin();
//		it != chunkResource.end();
//		it++)
//	{
//		Mix_FreeChunk(it->second);
//	}
//
//	//Quit SDL subsystems
//	TTF_Quit();
//	Mix_Quit();
//	IMG_Quit();
//	SDL_Quit();
//	return success;
//}
