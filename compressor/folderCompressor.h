#pragma once

class QString;
class QDataStream;

namespace compressor {

class FolderCompressor {
public:
	/// A recursive function that scans all files inside the source folder
	/// and serializes all files in a row of file names and compressed
	/// binary data in a single file.
	static bool compressFolder(const QString &sourceFolder, const QString &destinationFile);

	/// A function that deserializes data from the compressed file and
	/// creates any needed subfolders before saving the file.
	static bool decompressFolder(const QString &sourceFile, const QString &destinationFolder);

private:
	static bool compress(const QString &sourceFolder, const QString &prefix, QDataStream &dataStream);
};

}
