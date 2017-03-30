#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDir>
#include <QCryptographicHash>

#include <windows.h>
#include <stdio.h>
#include <cstring>




/**
 * @brief verifyOrCreateTargetDirectory
 * @param targetDirectory
 * @return
 */
bool verifyOrCreateTargetDirectory(QString targetDirectory);

/**
 * @brief getHash
 * @param filePath
 * @return
 */
const QString getHash(const QString& filePath);

/**
 * @brief getFullDirectory
 * @param target
 * @return
 */
QList<QString> getFullDirectory(QString target);

#endif // UTILS_H
