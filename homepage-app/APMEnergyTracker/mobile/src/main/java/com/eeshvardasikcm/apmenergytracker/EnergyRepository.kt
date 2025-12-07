package com.eeshvardasikcm.apmenergytracker

import android.content.Context
import android.util.Log
import com.google.android.gms.auth.api.signin.GoogleSignIn
import com.google.android.gms.fitness.Fitness
import com.google.android.gms.fitness.FitnessOptions
import com.google.android.gms.fitness.data.DataType
import com.google.android.gms.fitness.data.Field
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.tasks.await

/**
 * A singleton repository to manage and share energy data across the app, tile, and complication.
 */
object EnergyRepository {
    private const val TAG = "EnergyRepository"

    private val _energyExpended = MutableStateFlow(0f)
    val energyExpended = _energyExpended.asStateFlow()

    private val fitnessOptions = FitnessOptions.builder()
        .addDataType(DataType.TYPE_CALORIES_EXPENDED, FitnessOptions.ACCESS_READ)
        .build()

    /**
     * Reads the latest daily total for calories from Google Fit and updates the shared flow.
     * This is a suspending function, designed to be called from a coroutine.
     */
    suspend fun readEnergyData(context: Context) {
        val googleAccount = GoogleSignIn.getAccountForExtension(context, fitnessOptions)
        if (!GoogleSignIn.hasPermissions(googleAccount, fitnessOptions)) {
            Log.w(TAG, "Attempted to read data without permissions.")
            // In a real app, you might trigger a re-authentication flow here.
            // For Tiles/Complications, this will just fail silently.
            return
        }

        try {
            val response = Fitness.getHistoryClient(context, googleAccount)
                .readDailyTotal(DataType.TYPE_CALORIES_EXPENDED)
                .await() // Using await from coroutines library for cleaner async code

            val calories = response.getValue(Field.FIELD_CALORIES).asFloat()
            Log.d(TAG, "Repository successfully read calories: $calories")
            _energyExpended.value = calories
        } catch (e: Exception) {
            Log.e(TAG, "Failed to read daily total for calories from repository.", e)
        }
    }
}
