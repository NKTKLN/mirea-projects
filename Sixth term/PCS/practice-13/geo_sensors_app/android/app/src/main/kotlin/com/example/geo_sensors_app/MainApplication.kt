package com.example.geo_sensors_app

import android.app.Application
import com.yandex.mapkit.MapKitFactory

class MainApplication: Application() {
  override fun onCreate() {
    super.onCreate()
    MapKitFactory.setLocale("ru_RU"); 
    MapKitFactory.setApiKey("7ffcd96e-8c95-4129-9c13-a542756b556f");
  }
}