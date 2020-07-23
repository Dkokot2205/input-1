/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MERGINPROJECTMETADATA_H
#define MERGINPROJECTMETADATA_H

#include <QDateTime>
#include <QList>
#include <QJsonObject>

struct MerginFile
{
  QString path;
  QString checksum;
  qint64 size;
  QDateTime mtime;
  QStringList chunks; // used only for upload otherwise suppose to be empty

  //
  // these are members only used for upload of changed file through a geo-diff
  //

  QString diffName;          //!< if non-empty, we are uploading diff for this file and this is filename (relative to project's .mergin dir)
  QString diffChecksum;      //!< checksum for the diff file
  QString diffBaseChecksum;  //!< checksum of the base file
  qint64 diffSize;           //!< size (in bytes) of the diff file

  //
  // these are members only user for update of changed file through geodiff
  // (could be multiple diffs that need to be applied sequentially)
  //

  bool pullCanUseDiff = false;  //!< whether or not we can update the local file by downloading and applying diffs
  QList< QPair<int, int> > pullDiffFiles;   //!< list of diffs that will need to be fetched: the version and their sizes

  static MerginFile fromJsonObject( const QJsonObject &merginFileInfo );
};


//! Metadata read from project info reply or read from cached local .mergin.json file
// TODO add last_synced and owners for #776
struct MerginProjectMetadata
{
  QString name;
  QString projectNamespace;

  QList<int> writers;
  int version = -1;
  QList<MerginFile> files;

  // no project dir, no sync state, ...

  bool isValid() const { return !name.isEmpty() && !projectNamespace.isEmpty(); }

  static MerginProjectMetadata fromJson( const QByteArray &data );

  static MerginProjectMetadata fromCachedJson( const QString &metadataFilePath );

  MerginFile fileInfo( const QString &filePath ) const;
};


#endif // MERGINPROJECTMETADATA_H
