/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileRelated.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 00:57:28 by user42            #+#    #+#             */
/*   Updated: 2022/04/18 17:06:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILERELATED_HPP
#define FILERELATED_HPP

#include <string>
#include <vector>

//#include "stringRelated.hpp"
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <unistd.h>

std::string					formatDate(std::vector<std::string> vect);
std::string					buildDate();
std::string					formatLastModified(std::string path);
std::string					buildFileSize(std::string path);
std::string					formatETag(std::string &path);

#endif