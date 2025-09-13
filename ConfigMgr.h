#pragma once
#include "const.h"

struct SectionInfo {
	SectionInfo() {}
	~SectionInfo() {}

	SectionInfo(const SectionInfo& other) {
		_section_datas = other._section_datas;
	}

	SectionInfo& operator=(const SectionInfo& other) {
		if (this != &other) {
			_section_datas = other._section_datas;
		}
		return *this;
	}

	std::map<std::string, std::string> _section_datas;
	std::string operator[](const std::string& key) {
		auto it = _section_datas.find(key);
		if (it != _section_datas.end()) {
			return it->second;
		}
		return "";
	} 
};

class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_map.clear();
	}
	ConfigMgr();

	ConfigMgr& operator=(const ConfigMgr& src) {
		if (this == &src) return *this;
		_config_map = src._config_map;
		return *this;
	}
	static ConfigMgr& getInstance() {
		static ConfigMgr instance;
		return instance;
	}

	SectionInfo & operator[](const std::string& section) {
		return _config_map[section];
	}

private:
	std::map<std::string, SectionInfo> _config_map;
};

