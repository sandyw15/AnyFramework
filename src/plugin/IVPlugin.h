/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef IVPLUGIN_H_
#define IVPLUGIN_H_

#include "Plugin.h"
#include "PluginVersion.h"
#include "plugin/FactoryAPI.h"

namespace any_fw {

class IVPlugin : public PluginFW::CompositePlugin {
public:
	IVPlugin() : CompositePlugin(std::vector<PluginFW::Plugin*>()) {}
	virtual ~IVPlugin() {}

	void initialize(const PluginFW::PluginInfo& info);
	void addFactory(AnyItemFactory* factory) {
		factories.push_back(factory);
	}

	const PluginFW::PluginInfo& getInfo() { return info; }

private:
	std::vector<AnyItemFactory*> factories;
	PluginFW::PluginInfo info;
};

class AnyFactoryPlugin : public PluginFW::TypedPlugin<FactoryAPI > {
public:
	AnyFactoryPlugin(std::vector<AnyItemFactory*>& factories) : factories(factories) {}
	virtual ~AnyFactoryPlugin() {}

	void registerPlugin(FactoryAPI& api, PluginFW::PluginAPIInfo& apiInfo) {
		for (int f = 0; f < factories.size(); f++) {
			api.addFactory(factories[f]);
		}
	}
	void unregisterPlugin(FactoryAPI& api, PluginFW::PluginAPIInfo& apiInfo) {}

private:
	std::vector<AnyItemFactory*>& factories;
};


} /* namespace any_fw */

inline void any_fw::IVPlugin::initialize(const PluginFW::PluginInfo& info) {
	addPlugin(new AnyFactoryPlugin(factories));
	this->info = info;
	PluginFW::CompositePlugin::initialize(info);
}


#endif /* IVPLUGIN_H_ */
