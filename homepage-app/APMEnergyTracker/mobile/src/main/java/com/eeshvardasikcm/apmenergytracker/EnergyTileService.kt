package com.eeshvardasikcm.apmenergytracker

import androidx.core.content.ContextCompat
import androidx.wear.protolayout.ColorBuilders
import androidx.wear.protolayout.DeviceParametersBuilders
import androidx.wear.protolayout.DimensionBuilders
import androidx.wear.protolayout.LayoutElementBuilders
import androidx.wear.protolayout.material.CompactChip
import androidx.wear.protolayout.material.Text
import androidx.wear.protolayout.material.Typography
import androidx.wear.protolayout.material.layouts.PrimaryLayout
import androidx.wear.tiles.RequestBuilders
import androidx.wear.tiles.TileBuilders
import com.google.android.horologist.annotations.ExperimentalHorologistApi
import com.google.android.horologist.tiles.SuspendingTileService
import kotlinx.coroutines.flow.first

@OptIn(ExperimentalHorologistApi::class)
class EnergyTileService : SuspendingTileService() {

    override suspend fun resourcesRequest(requestParams: RequestBuilders.ResourcesRequest): TileBuilders.Resources {
        // No resources needed for this simple tile
        return TileBuilders.Resources.Builder().build()
    }

    override suspend fun tileRequest(requestParams: RequestBuilders.TileRequest): TileBuilders.Tile {
        // Fetch the latest data from the repository
        EnergyRepository.readEnergyData(this)
        val energyValue = EnergyRepository.energyExpended.first()

        val layout = tileLayout(
            context = this,
            deviceParameters = requestParams.deviceConfiguration,
            energyValue = energyValue
        )

        return TileBuilders.Tile.Builder()
            .setResourcesVersion("1")
            .setTileTimeline(
                TileBuilders.Timeline.fromLayoutElement(layout)
            ).build()
    }

    private fun tileLayout(
        context: EnergyTileService,
        deviceParameters: DeviceParametersBuilders.DeviceParameters,
        energyValue: Float
    ): LayoutElementBuilders.LayoutElement {
        return PrimaryLayout.Builder(deviceParameters)
            .setPrimaryLabelTextContent(
                Text.Builder(context, "Energy")
                    .setTypography(Typography.TYPOGRAPHY_CAPTION1)
                    .setColor(ColorBuilders.argb(ContextCompat.getColor(context, R.color.primary)))
                    .build()
            )
            .setContent(
                LayoutElementBuilders.Column.Builder()
                    .addContent(
                        Text.Builder(context, "%.0f".format(energyValue))
                            .setTypography(Typography.TYPOGRAPHY_DISPLAY1)
                            .setColor(ColorBuilders.argb(ContextCompat.getColor(context, R.color.on_surface)))
                            .build()
                    )
                    .addContent(
                        Text.Builder(context, "kcal")
                            .setTypography(Typography.TYPOGRAPHY_TITLE3)
                            .setColor(ColorBuilders.argb(ContextCompat.getColor(context, R.color.on_surface_variant)))
                            .build()
                    )
                    .build()
            )
            .setPrimaryChipContent(
                CompactChip.Builder(context, "Sync", { /* TODO: Add sync action */ }, deviceParameters)
                    .build()
            )
            .build()
    }
}
