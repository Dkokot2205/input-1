/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/


#ifndef BROWSEDATALAYERSMODEL_H
#define BROWSEDATALAYERSMODEL_H

#include <QObject>

#include "qgsmaplayerproxymodel.h"
#include "qgsmaplayermodel.h"
#include "qgsvectorlayer.h"
#include "qgsmaplayer.h"
#include "qgsproject.h"
#include "qgslayertree.h"
#include "qgslayertreelayer.h"

#include "alayersmodel.h"

enum ModelTypes
{
  ActiveLayerSelection,
  BrowseDataLayerSelection,
  MapSettingsLayers,
  AllLayers
};

class LayersProxyModel : public QgsMapLayerProxyModel
{
    Q_OBJECT

  public:
    LayersProxyModel( ALayersModel *model, ModelTypes modelType = ModelTypes::AllLayers );

    bool filterAcceptsRow( int source_row, const QModelIndex &source_parent ) const override;

    //! Returns layers regarding model type
    Q_INVOKABLE QList<QgsMapLayer *> layers() const;

  private:

    //! returns if input layer is capable of recording new features
    bool recordingAllowed( QgsMapLayer *layer ) const;

    //! filters if input layer should be visible for browsing
    bool browsingAllowed( QgsMapLayer *layer ) const;

    //! filters if input layer should be visible in map settings
    bool layerVisible( QgsMapLayer *layer ) const;

    ModelTypes mModelType;
    ALayersModel *mModel;

    std::function<bool( QgsMapLayer * )> filterFunction;
};

#endif // BROWSEDATALAYERSMODEL_H
