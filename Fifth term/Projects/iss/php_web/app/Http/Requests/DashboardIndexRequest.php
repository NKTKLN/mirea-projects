<?php

namespace App\Http\Requests;

use Illuminate\Foundation\Http\FormRequest;
use Illuminate\Validation\Rule;

class DashboardIndexRequest extends FormRequest
{
    public const ALLOWED_SORTS = ['id', 'latitude', 'longitude', 'visibility', 'fetched_at'];
    public const ALLOWED_ORDERS = ['asc', 'desc'];

    public function authorize(): bool
    {
        return true;
    }

    public function rules(): array
    {
        return [
            'search' => ['nullable', 'string', 'max:120'],
            'sort_by' => ['nullable', 'string', Rule::in(self::ALLOWED_SORTS)],
            'sort_order' => ['nullable', 'string', Rule::in(self::ALLOWED_ORDERS)],
            'page' => ['nullable', 'integer', 'min:1'],
        ];
    }

    public function filters(): array
    {
        $validated = $this->validated();

        return [
            'search' => $validated['search'] ?? null,
            'sort_by' => $validated['sort_by'] ?? 'fetched_at',
            'sort_order' => $validated['sort_order'] ?? 'desc',
            'per_page' => 15,
        ];
    }
}
