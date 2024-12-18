#pragma once

#include <filesystem>

#include <vfs.h>

std::vector<std::string> blacklist = { ".fnt", ".atl", ".lua", ".fs", ".vs"};

void cook()
{
	PakToc toc;

	pakTocInit(&toc);

	int current_pak_file = 0;
	int bytes_written = 0;

	std::ofstream current_data_pak_stream = std::ofstream("data/game_0.thetapak", std::ios::binary | std::ios::out);
	std::stringstream compression_stream;



	for (auto& path : std::filesystem::recursive_directory_iterator(std::filesystem::path("../data")))
	{
		if (path.is_directory())
			continue;

		PakEntry p;

		// remove ../../../data/ from path
		auto path_string = path.path().string();
		path_string = path_string.substr(8, path_string.size() - 8);
		std::replace(path_string.begin(), path_string.end(), '\\', '/');


		// get extension
		auto extension = path.path().extension().string();

		log_info("Packing %s to pak: %d", path_string.c_str(), current_pak_file);

		strcpy(p.path, path_string.c_str());

		auto file_data = utils::file::ReadAllBytes(path.path().string());
		p.data_size = file_data.size();

		if (p.data_size == 0)
			continue;

		// check if pak is larger than 5mb
		if (bytes_written > 5242880 && false)
		{
			toc.num_data_paks++;
			current_pak_file++;
			current_data_pak_stream.close();
			current_data_pak_stream.open("data/game_" + std::to_string(current_pak_file) + ".thetapak", std::ios::binary | std::ios::out);
			bytes_written = 0;
		}

		p.pak_number = current_pak_file;

		if (std::find(blacklist.begin(), blacklist.end(), extension) == blacklist.end())
		{

			p.data_offset = bytes_written;
			p.compressed = 0;

			current_data_pak_stream.write(file_data.data(), file_data.size());
			bytes_written += file_data.size();
		}
		else
		{
			std::filesystem::path target = "data/" + path_string;

			log_info("target path: %s", target.c_str());

			auto src = path.path().string();
			auto targetPath = target;
			targetPath.remove_filename();

			try {

			std::filesystem::create_directories(targetPath); // Recursively create target directory if not existing.
			std::filesystem::copy_file(src, target, std::filesystem::copy_options::overwrite_existing);
			}
			catch (std::filesystem::filesystem_error& ex)
			{
				log_error("%s", ex.what());
			}
			
			continue;
		}

		pakTocEntryPush(&toc, p);
	}

	std::ofstream toc_stream("data/game.thetatoc", std::ios::binary | std::ios::out);


	toc_stream.write(toc.magic, 4);
	toc_stream.write((char*)&toc.num_data_paks, sizeof(uint32_t));
	toc_stream.write((char*)&toc.num_files, sizeof(uint32_t));

	if (toc.num_files > 0)
		toc_stream.write((char*)toc.data_entries, sizeof(PakEntry) * toc.num_files);

	toc_stream.close();

	log_info("Packed total: %d files", toc.num_files);
	return;
}