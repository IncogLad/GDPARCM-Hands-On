#pragma once
#include <unordered_map>

#include "IExecutionEvent.h"
#include "ThreadPool.h"
#include "SFML/Graphics.hpp"

class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> TextureTable;

public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadSingleStreamAsset(int index, IExecutionEvent* i_execution_event); //loads a single streaming asset based on index in directory
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(int index);
	int getNumLoadedStreamTextures() const;

	void countStreamingAssets();
	void instantiateAsTexture(String path, String assetName, bool isStreaming);

	int streamingAssetCount = 0;

private:
	TextureManager();
	~TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	TextureTable texture_table_;
	TextureList base_texture_list_;
	TextureList stream_texture_list_;

	const std::string STREAMING_PATH = "Media/Streaming/";
	
	ThreadPool* threadPool;

};
