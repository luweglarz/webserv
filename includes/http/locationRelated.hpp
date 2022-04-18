/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locationRelated.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 00:57:32 by user42            #+#    #+#             */
/*   Updated: 2022/04/18 16:45:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONRELATED_HPP
#define LOCATIONRELATED_HPP


//#include "pathRelated.hpp"
#include "Config.hpp"

std::pair<bool,LocationContext>  		pathIsLocation(std::string path,const std::vector<LocationContext> &serverLocation, std::string directiveName);
std::pair<bool,LocationContext>  		getLocation(std::string path,const std::vector<LocationContext> &serverLocation);
std::vector<std::string>				retrieveDirectiveArgs(LocationContext const &location, std::string directiveName);
bool									isMethodAllowed(std::vector<LocationContext> locations, std::string path, std::string method);
std::string								checkIndex(std::string rootPath, std::vector<std::string> index);
std::pair<std::string, std::string>		retrieveLocationIndex(std::vector<LocationContext> locations, std::string rootPath, std::string path);

std::map<std::string, std::string>		initExtensionTypes();

#endif