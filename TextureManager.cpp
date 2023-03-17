#include <fstream>
#include <iostream>
#include "TextureManager.h"
#include "StringUtils.h"
#include <filesystem>

#include <thread>

#include "LoadingStatus.h"
#include "StreamLoaderThread.h"


TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager* TextureManager::getInstance()
{
	if (sharedInstance == nullptr) sharedInstance = new TextureManager();

	return sharedInstance;
}

TextureManager::TextureManager()
{
	this->countStreamingAssets();

	//init threadPool at the start
	this->threadPool = new ThreadPool("threadPool", 10);
	this->threadPool->startScheduler();
}

TextureManager::~TextureManager()
{
	this->threadPool->stopScheduler();
}

void TextureManager::loadFromAssetList()
{
	//std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while (std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		//std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::loadSingleStreamAsset(int index, IExecutionEvent* i_execution_event)
{
	int fileNum = 0;

	for ( auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			StreamLoaderThread* stream_loader_thread = new StreamLoaderThread(entry.path().string(), i_execution_event);
			this->threadPool->scheduleTask(stream_loader_thread);

			break;
		}

		fileNum++;
		///std::cout << fileNum << std::endl;
	}


}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->texture_table_[assetName].empty()) {
		return this->texture_table_[assetName][frameIndex];
	}
	else {
		//std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!this->texture_table_[assetName].empty()) {
		return this->texture_table_[assetName].size();
	}
	else {
		//std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getStreamTextureFromList(int index)
{
	return this->stream_texture_list_[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->stream_texture_list_.size();
}

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streamingAssetCount++;
	}

	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
	LoadingStatus::getInstance()->setMaxItems(this->streamingAssetCount);
}

void TextureManager::instantiateAsTexture(String path, String assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->texture_table_[assetName].push_back(texture);

	if (isStreaming)
	{
		this->stream_texture_list_.push_back(texture);
	}
	else
	{
		this->base_texture_list_.push_back(texture);
	}

}