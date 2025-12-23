<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Arr;

class DashboardController extends Controller
{
    public function index(Request $request)
    {
        $records = collect();
        $apiError = false;

        $search    = $request->get('search');
        $sortBy    = $request->get('sort_by', 'fetched_at');
        $sortOrder = $request->get('sort_order', 'desc');

        try {
            $response = Http::timeout(3)->get(config('services.rust_api.url'));

            if ($response->ok() && is_array($response->json('data'))) {
                $records = collect($response->json('data'));

                if ($search) {
                    $records = $records->filter(function ($r) use ($search) {
                        return str_contains(strtolower($r['visibility']), strtolower($search))
                            || str_contains((string)$r['latitude'], $search)
                            || str_contains((string)$r['longitude'], $search)
                            || str_contains((string)$r['id'], $search);
                    });
                }

                if (in_array($sortBy, ['id', 'latitude', 'longitude', 'visibility', 'fetched_at'])) {
                    $records = $sortOrder === 'asc'
                        ? $records->sortBy($sortBy)
                        : $records->sortByDesc($sortBy);
                }

                $records = $records->values();
            } else {
                $apiError = true;
            }
        } catch (\Throwable $e) {
            $apiError = true;
            Log::warning('Rust API unavailable', ['error' => $e->getMessage()]);
        }

        return view('dashboard', compact(
            'records',
            'search',
            'sortBy',
            'sortOrder',
            'apiError'
        ));
    }
}
