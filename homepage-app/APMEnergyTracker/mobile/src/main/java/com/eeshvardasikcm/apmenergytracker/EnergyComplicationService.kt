package com.eeshvardasikcm.apmenergytracker

import android.app.PendingIntent
import android.content.Intent
import androidx.wear.watchface.complications.data.ComplicationData
import androidx.wear.watchface.complications.data.ComplicationType
import androidx.wear.watchface.complications.data.PlainComplicationText
import androidx.wear.watchface.complications.data.ShortTextComplicationData
import androidx.wear.watchface.complications.datasource.ComplicationRequest
import com.google.android.horologist.annotations.ExperimentalHorologistApi
import com.google.android.horologist.complications.SuspendingComplicationDataSourceService
import kotlinx.coroutines.flow.first

@OptIn(ExperimentalHorologistApi::class)
class EnergyComplicationService : SuspendingComplicationDataSourceService() {

    override suspend fun onComplicationRequest(request: ComplicationRequest): ComplicationData? {
        // Fetch the latest data from the repository
        EnergyRepository.readEnergyData(this)
        val energyValue = EnergyRepository.energyExpended.first()

        // Create the complication data. This service only supports SHORT_TEXT.
        return when (request.complicationType) {
            ComplicationType.SHORT_TEXT -> ShortTextComplicationData.Builder(
                text = PlainComplicationText.Builder("%.0f".format(energyValue)).build(),
                contentDescription = PlainComplicationText.Builder("Energy in kcal").build()
            )
                .setTitle(PlainComplicationText.Builder("Energy").build())
                .setTapAction(createTapAction())
                .build()
            else -> null // Return null for unsupported complication types
        }
    }

    override fun getPreviewData(type: ComplicationType): ComplicationData? {
        // Provide static preview data for the watch face customization screen
        return when (type) {
            ComplicationType.SHORT_TEXT -> ShortTextComplicationData.Builder(
                text = PlainComplicationText.Builder("1234").build(),
                contentDescription = PlainComplicationText.Builder("Energy in kcal").build()
            )
                .setTitle(PlainComplicationText.Builder("Energy").build())
                .build()
            else -> null
        }
    }

    private fun createTapAction(): PendingIntent? {
        val intent = Intent(this, MainActivity::class.java)
        return PendingIntent.getActivity(
            this, 0, intent,
            PendingIntent.FLAG_UPDATE_CURRENT or PendingIntent.FLAG_IMMUTABLE
        )
    }
}
