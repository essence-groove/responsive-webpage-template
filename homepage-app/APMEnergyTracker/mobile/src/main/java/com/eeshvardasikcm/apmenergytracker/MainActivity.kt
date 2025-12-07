package com.eeshvardasikcm.apmenergytracker

import android.app.Activity
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.rounded.Favorite
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.rememberCoroutineScope
import androidx.lifecycle.lifecycleScope
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.style.TextAlign
import androidx.wear.compose.material.Button
import androidx.wear.compose.material.Icon
import androidx.wear.compose.material.Text
import com.eeshvardasikcm.apmenergytracker.ui.theme.AyurvedaEnergyTrackerTheme
import com.google.android.gms.auth.api.signin.GoogleSignIn
import com.google.android.gms.fitness.FitnessOptions
import com.google.android.gms.fitness.data.DataType
import kotlinx.coroutines.launch

class MainActivity : ComponentActivity() {

    private val TAG = "APMEnergyTracker"

    private val fitnessOptions = FitnessOptions.builder()
        .addDataType(DataType.TYPE_CALORIES_EXPENDED, FitnessOptions.ACCESS_READ)
        .build()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Check for Google Fit permissions on app start
        checkPermissionsAndRun()

        setContent {
            val scope = rememberCoroutineScope()
            // Collect the energy value as state from the shared repository
            val energyValue by EnergyRepository.energyExpended.collectAsState()

            AyurvedaEnergyTrackerTheme {
                EnergyTrackerScreen(
                    energyValue = energyValue,
                    onSyncClick = {
                        scope.launch {
                            EnergyRepository.readEnergyData(this@MainActivity)
                        }
                    }
                )
            }
        }
    }

    private fun checkPermissionsAndRun() {
        val googleAccount = GoogleSignIn.getAccountForExtension(this, fitnessOptions)
        if (!GoogleSignIn.hasPermissions(googleAccount, fitnessOptions)) {
            // Request permissions if not already granted
            googleSignInLauncher.launch(
                GoogleSignIn.getClient(this, fitnessOptions).signInIntent
            )
        } else {
            // Permissions are already granted, read initial data
            // Use a coroutine to call the suspend function
            lifecycleScope.launch {
                EnergyRepository.readEnergyData(this@MainActivity)
            }
        }
    }

    // Launcher to handle the result of the Google Sign-In/permission request
    private val googleSignInLauncher = registerForActivityResult(
        ActivityResultContracts.StartActivityForResult()
    ) { result ->
        if (result.resultCode == Activity.RESULT_OK) {
            Log.d(TAG, "Google Fit permission granted.")
            // Permissions granted, now read the data
            lifecycleScope.launch {
                EnergyRepository.readEnergyData(this@MainActivity)
            }
        } else {
            Log.e(TAG, "Google Fit permission denied.")
            // Handle the case where the user denies permissions
        }
    }
}

@Composable
fun EnergyTrackerScreen(energyValue: Float, onSyncClick: () -> Unit) {
    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = "Ayurveda Energy",
            textAlign = TextAlign.Center
        )
        Text(
            text = "%.0f".format(energyValue) + " kcal",
            textAlign = TextAlign.Center,
            modifier = Modifier.weight(1f)
        )
        Button(onClick = onSyncClick) {
            Icon(
                imageVector = Icons.Rounded.Favorite,
                contentDescription = "Sync with Google Fit"
            )
        }
    }
}
