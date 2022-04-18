/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locationRelated.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 00:58:14 by user42            #+#    #+#             */
/*   Updated: 2022/04/18 17:06:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//pas sur
#include "stringRelated.hpp"
#include "locationRelated.hpp"
#include "pathRelated.hpp"

std::pair<bool,LocationContext>  pathIsLocation(std::string path,const std::vector<LocationContext> &serverLocation, std::string directiveName){
	LocationContext init;
	std::pair<bool,LocationContext> locationPair = std::make_pair(true, init);

	for (size_t i = 0; i < serverLocation.size(); i++){
		if ((path.append("/").find(serverLocation[i].args[0]) != std::string::npos) && 
			((serverLocation[i].directives.count(directiveName) == 1) || (serverLocation[i].directives.count(directiveName) == 1))){
			locationPair.second = serverLocation[i];
			return(locationPair);
		}
	}
	locationPair.first = false;
	return (locationPair);
}

std::pair<bool,LocationContext>  getLocation(std::string path,const std::vector<LocationContext> &serverLocation){
	LocationContext 				init;
	std::pair<bool,LocationContext> locationPair = std::make_pair(true, init);
	
	for (size_t i = 0; i < serverLocation.size(); i++){
		if ((path.append("/").find(serverLocation[i].args[0]) != std::string::npos && path.find(serverLocation[i].directives.find("cgi_extension")->second[0]) != std::string::npos) ||
			(match(serverLocation[i].args[0].c_str(), path.c_str(), '*') == true) ){
			locationPair.second = serverLocation[i];
			return(locationPair);
		}
	}
	locationPair.first = false;
	return (locationPair);
}

std::vector<std::string>				retrieveDirectiveArgs(LocationContext const &location, std::string directiveName){
	(void)directiveName;
	std::vector<std::string> ret;
	try{
		ret = (*location.directives.find(directiveName)).second;
	}
	catch (std::exception &e){
	}
	return (ret);
}

bool						isMethodAllowed(std::vector<LocationContext> locations, std::string path, std::string method){
	std::pair<bool,LocationContext> isLocation = pathIsLocation(path, locations, "limit_except");
	if (isLocation.first == false)
		return (true);

	std::vector<std::string> limits = retrieveDirectiveArgs(isLocation.second, "limit_except");
	for (size_t i = 0; i < limits.size(); i++){
		if (method == limits.at(i))
			return (false);
	}
	return (true);
}

std::string					checkIndex(std::string rootPath, std::vector<std::string> index){
	std::string ret;

	for (std::vector<std::string>::iterator it = index.begin(); it != index.end(); it++){
		if (isPathValid(buildPathTo(rootPath, *it, "")) == true)
			return (*it);
	}
	return ("default_index.html");
}

std::pair<std::string, std::string>				retrieveLocationIndex(std::vector<LocationContext> locations, std::string rootPath, std::string path){
	std::pair<std::string, std::string> ret; 

	std::pair<bool,LocationContext> isLocation = pathIsLocation(path, locations, "index");
	if (isLocation.first == false)
		return (ret);
	std::vector<std::string> index = retrieveDirectiveArgs(isLocation.second, "index");
	ret.first = checkIndex(rootPath, index);
	ret.second = isLocation.second.args[0];
	return (ret);
}

std::map<std::string, std::string>	initExtensionTypes(){
	std::map<std::string, std::string> ret;

	//Text
	ret.insert(std::make_pair("css", "text/css"));
	ret.insert(std::make_pair("csv", "text/csv"));
	ret.insert(std::make_pair("html", "text/html"));
	ret.insert(std::make_pair("htm", "text/html"));
	ret.insert(std::make_pair("ics", "text/calendar"));
	ret.insert(std::make_pair("js", "text/javascript"));
	ret.insert(std::make_pair("txt", "text/plain"));
	//Image
	ret.insert(std::make_pair("bmp", "image/bmp"));
	ret.insert(std::make_pair("gif", "image/gif"));
	ret.insert(std::make_pair("ico", "image/vnd.microsoft.icon"));
	ret.insert(std::make_pair("jpeg", "image/jpeg"));
	ret.insert(std::make_pair("jpg", "image/jpeg"));
	ret.insert(std::make_pair("png", "image/png"));
	ret.insert(std::make_pair("svg", "image/svg+xml"));
	ret.insert(std::make_pair("tif", "image/tiff"));
	ret.insert(std::make_pair("webp", "image/webp"));
	//Audio
	ret.insert(std::make_pair("aac", "audio/aac"));
	ret.insert(std::make_pair("mid", "audio/midi"));
	ret.insert(std::make_pair("midi", "audio/midi"));
	ret.insert(std::make_pair("audio", "audio/mpeg"));
	ret.insert(std::make_pair("ogg", "audio/ogg"));
	ret.insert(std::make_pair("opus", "audio/opus"));
	ret.insert(std::make_pair("wav", "audio/wav"));
	ret.insert(std::make_pair("weba", "audio/webn"));
	//Video
	ret.insert(std::make_pair("avi", "video/x-msvideo"));
	ret.insert(std::make_pair("mpeg", "video/mpeg"));
	ret.insert(std::make_pair("ogv", "video/ogg"));
	ret.insert(std::make_pair("ts", "video/mp2t"));
	ret.insert(std::make_pair("webm", "video/webm"));
	ret.insert(std::make_pair("3gp", "video/3gpp"));
	ret.insert(std::make_pair("3g2", "video/3gpp2"));
	//Application
	ret.insert(std::make_pair("abw", "application/x-abiword"));
	ret.insert(std::make_pair("arc", "application/x-freearc"));
	ret.insert(std::make_pair("azw", "application/vnd.amazon.ebook"));
	ret.insert(std::make_pair("bin", "application/octet-stream"));
	ret.insert(std::make_pair("bz", "application/x-bzip"));
	ret.insert(std::make_pair("bz2", "application/x-bzip2"));
	ret.insert(std::make_pair("csh", "application/x-csh"));
	ret.insert(std::make_pair("doc", "application/msword"));
	ret.insert(std::make_pair("docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"));
	ret.insert(std::make_pair("eot", "application/vnd.ms-fontobject"));
	ret.insert(std::make_pair("epub", "application/epub+zip"));
	ret.insert(std::make_pair("gz", "application/gzip"));
	ret.insert(std::make_pair("jar", "application/java-archive"));
	ret.insert(std::make_pair("json", "application/json"));
	ret.insert(std::make_pair("jsonld", "application/ld+json"));
	ret.insert(std::make_pair("mpkg", "application/vnd.apple.installer+xml"));
	ret.insert(std::make_pair("odp", "application/vnd.oasis.opendocument.presentation"));
	ret.insert(std::make_pair("ods", "application/vnd.oasis.opendocument.spreadsheet"));
	ret.insert(std::make_pair("odt", "application/vnd.oasis.opendocument.text"));
	ret.insert(std::make_pair("ogx", "application/ogg"));
	ret.insert(std::make_pair("pdf", "application/pdf"));
	ret.insert(std::make_pair("php", "application/x-httpd-php"));
	ret.insert(std::make_pair("ppt", "application/vnd.ms-powerpoint"));
	ret.insert(std::make_pair("pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"));
	ret.insert(std::make_pair("rar", "application/vnd.rar"));
	ret.insert(std::make_pair("rtf", "application/rtf"));
	ret.insert(std::make_pair("sh", "application/x-sh"));
	ret.insert(std::make_pair("swf", "application/x-shockwave-flash"));
	ret.insert(std::make_pair("tar", "application/x-tar"));
	ret.insert(std::make_pair("vsd", "application/vnd.visio"));
	ret.insert(std::make_pair("xhtml", "application/xhtml+xml"));
	ret.insert(std::make_pair("xls", "application/vnd.ms-excel"));
	ret.insert(std::make_pair("xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"));
	ret.insert(std::make_pair("xml", "application/xml"));
	ret.insert(std::make_pair("xul", "application/vnd.mozilla.xul+xml"));
	ret.insert(std::make_pair("zip", "application/zip"));
	ret.insert(std::make_pair("7z", "application/x-7z-compressed"));

	return (ret);
}