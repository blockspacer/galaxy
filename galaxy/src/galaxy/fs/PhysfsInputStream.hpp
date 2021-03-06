///
/// PhysfsInputStream.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_PHYSFSINPUTSTREAM_HPP_
#define GALAXY_PHYSFSINPUTSTREAM_HPP_

#include <string>

#include <SFML/System/InputStream.hpp>

// Forward dec.
struct PHYSFS_File;

///
/// Core namespace.
///
namespace galaxy
{
    ///
    /// An SFML input stream that utilizes Physfs.
    ///
	class PhysfsInputStream final : public sf::InputStream
	{
    public:
        ///
        /// Default constructor.
        ///
        PhysfsInputStream() noexcept;

        ///
        /// \brief Argument constructor.
        ///
        /// Can throw exceptions.
        ///
        /// \param file Filename matching a file that exists in the PhysFS filesystem.
        ///
        explicit PhysfsInputStream(const std::string& file);

        ///
        /// Destructor.
        ///
        ~PhysfsInputStream() noexcept override;

        ///
        /// \brief Opens a file using PhysFS.
        ///
        /// Can throw exceptions.
        ///
        /// \param file Filename matching a file that exists in the PhysFS filesystem.
        ///
        /// \return True if successful.
        ///
        bool open(const std::string& file);

        ///
        /// Closes file in PhysFS.
        ///
        void close() noexcept;

        ///
        /// \brief Read data from the stream
        ///
        /// After reading, the stream's reading position must be
        /// advanced by the amount of bytes read.
        ///
        /// \param data Buffer where to copy the read data
        /// \param size Desired number of bytes to read
        ///
        /// \return The number of bytes actually read, or -1 on error
        ///
        sf::Int64 read(void* data, sf::Int64 size) noexcept override;

        ///
        /// \brief Change the current reading position
        ///
        /// \param position The position to seek to, from the beginning
        ///
        /// \return The position actually sought to, or -1 on error
        ///
        sf::Int64 seek(sf::Int64 position) noexcept override;

        ///
        /// \brief Get the current reading position in the stream
        ///
        /// \return The current position, or -1 on error.
        ///
        sf::Int64 tell() noexcept override;

        ///
        /// \brief Return the size of the stream
        ///
        /// \return The total number of bytes available in the stream, or -1 on error
        ///
        sf::Int64 getSize() noexcept override;

        ///
        /// Is the file currently open.
        ///
        /// \return True if file is open.
        ///
        const bool isOpen() const noexcept;

    private:
        ///
        /// Flag to check if file has been opened.
        ///
        bool m_opened;

        ///
        /// PhysFS handle.
        ///
        PHYSFS_File* m_file;
	};
}

#endif