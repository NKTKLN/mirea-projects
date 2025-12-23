<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\DashboardController;

// Главная страница ведет сразу на наш Дашборд
Route::get('/', [DashboardController::class, 'index']);