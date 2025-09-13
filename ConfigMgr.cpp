#include "ConfigMgr.h"

ConfigMgr::ConfigMgr() {
	boost::filesystem::path config_path = boost::filesystem::current_path();
	config_path /= "config.ini";
	std::cout << "config path: " << config_path.string() << std::endl;

	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(config_path.string(), pt);
	for (const auto& section : pt) {
		const std::string& section_name = section.first;
		SectionInfo& section_info = _config_map[section_name];
		for (const auto& key_value : section.second) {
			const std::string& key = key_value.first;
			const std::string& value = key_value.second.get_value<std::string>();
			section_info._section_datas[key] = value;
		}
	}

	//遍历_config_map打印所有配置项
	for (const auto& section_pair : _config_map) {
		const std::string& section_name = section_pair.first;
		const SectionInfo& section_info = section_pair.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value : section_info._section_datas) {
			std::cout << key_value.first << " = " << key_value.second << std::endl;
		}
	}
}