#ifndef LOCATIONRELATED_HPP
#define LOCATIONRELATED_HPP

#include "pathRelated.hpp"
#include "Client.hpp"

std::pair<bool,LocationContext>  		pathIsLocation(std::string path,const std::vector<LocationContext> &serverLocation, std::string directiveName);
std::pair<bool,LocationContext>  		getLocation(std::string path,const std::vector<LocationContext> &serverLocation);
std::vector<std::string>				retrieveDirectiveArgs(LocationContext const &location, std::string directiveName);
bool									isMethodAllowed(std::vector<LocationContext> locations, std::string path, std::string method);
std::string								checkIndex(std::string rootPath, std::vector<std::string> index);
std::pair<std::string, std::string>		retrieveLocationIndex(std::vector<LocationContext> locations, std::string rootPath, std::string path);

#endif