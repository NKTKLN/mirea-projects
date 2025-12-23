<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Space Dashboard • ISS Monitor</title>

    <!-- Bootstrap (нужен для пагинации bootstrap-5 и базовой сетки) -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">

    <style>
        :root{
            --bg0: #060814;
            --bg1: #0b1026;
            --card: rgba(255,255,255,.06);
            --card2: rgba(255,255,255,.08);
            --stroke: rgba(255,255,255,.10);
            --text: #e8ecff;
            --muted: rgba(232,236,255,.65);
            --accent: #7c3aed; /* violet */
            --accent2:#22d3ee; /* cyan */
            --good:#22c55e;
            --warn:#60a5fa;
            --shadow: 0 18px 50px rgba(0,0,0,.45);
        }

        body{
            min-height: 100vh;
            color: var(--text);
            background:
                radial-gradient(1200px 600px at 10% 10%, rgba(124,58,237,.28), transparent 60%),
                radial-gradient(1000px 700px at 90% 15%, rgba(34,211,238,.22), transparent 55%),
                radial-gradient(900px 700px at 50% 95%, rgba(99,102,241,.18), transparent 55%),
                linear-gradient(180deg, var(--bg0), var(--bg1));
            font-family: ui-sans-serif, system-ui, -apple-system, Segoe UI, Roboto, Arial, "Noto Sans", "Apple Color Emoji", "Segoe UI Emoji";
        }

        .shell{
            max-width: 1100px;
        }

        .card-glass{
            background: var(--card);
            border: 1px solid var(--stroke);
            border-radius: 18px;
            box-shadow: var(--shadow);
            backdrop-filter: blur(12px);
        }

        .topbar{
            position: relative;
            overflow: hidden;
        }

        .topbar:before{
            content:"";
            position:absolute;
            inset:-2px;
            background: radial-gradient(600px 200px at 20% 0%, rgba(124,58,237,.35), transparent 60%),
                        radial-gradient(600px 220px at 80% 0%, rgba(34,211,238,.28), transparent 60%);
            opacity:.7;
            pointer-events:none;
        }

        .topbar .inner{
            position: relative;
            padding: 22px 22px;
        }

        .subtitle{ color: var(--muted); }

        .form-control, .form-select{
            background: rgba(0,0,0,.18) !important;
            border: 1px solid rgba(255,255,255,.14) !important;
            color: var(--text) !important;
            border-radius: 12px !important;
        }
        .form-control::placeholder{ color: rgba(232,236,255,.45); }

        .btn-accent{
            border: 0;
            border-radius: 12px;
            color: white;
            padding: .65rem 1rem;
            background: linear-gradient(135deg, var(--accent), var(--accent2));
            box-shadow: 0 10px 25px rgba(124,58,237,.25);
        }
        .btn-accent:hover{
            filter: brightness(1.05);
            transform: translateY(-1px);
        }

        /* === TABLE WRAPPER === */
        .table-wrap{
            overflow: hidden;
            border-radius: 18px;
        }

        /* === TABLE BASE === */
        .table{
            margin-bottom: 0;
            width: 100%;
            color: var(--text);
            background: rgba(6, 8, 20, 0.85);
        }

        .table {
            --bs-table-bg: transparent;
            --bs-table-color: var(--text);
            --bs-table-border-color: rgba(255,255,255,.08);
            --bs-table-hover-bg: transparent;
            --bs-table-striped-bg: transparent;
        }

        .table tbody tr{
            background-color: rgba(8, 12, 32, 0.85) !important;
            transition: background .25s ease, transform .15s ease;
        }

        .table tbody tr:nth-child(even){
            background-color: rgba(10, 14, 40, 0.9) !important;
        }

        .table thead th {
            background-color: rgba(20, 24, 60, 0.95);
        }

        /* === TABLE HEADER === */
        .table thead th{
            background: linear-gradient(
                180deg,
                rgba(124,58,237,.35),
                rgba(34,211,238,.18)
            );
            color: #f1f5ff;
            font-weight: 600;
            letter-spacing: .03em;
            padding: 14px;
            border-bottom: 1px solid rgba(255,255,255,.18);
        }

        /* === TABLE ROWS === */
        .table tbody tr{
            background: rgba(8, 12, 32, 0.75);
            transition: background .25s ease, transform .15s ease;
        }

        .table tbody tr:nth-child(even){
            background: rgba(10, 14, 40, 0.85);
        }

        .table tbody tr:hover{
            background: linear-gradient(
                90deg,
                rgba(124,58,237,.28),
                rgba(34,211,238,.20)
            );
            transform: translateY(-1px);
        }

        /* === TABLE CELLS === */
        .table tbody td{
            padding: 14px;
            border-bottom: 1px solid rgba(255,255,255,.08);
            color: rgba(232,236,255,.95);
            vertical-align: middle;
        }

        /* === MONO TEXT === */
        .mono{
            font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace;
            font-size: .95em;
            color: #e8ecff;
        }

        /* === BADGES === */
        .badge-pill{
            display: inline-flex;
            align-items: center;
            gap: .4rem;
            padding: 6px 12px;
            border-radius: 999px;
            font-weight: 700;
            font-size: .85rem;
            letter-spacing: .01em;
            border: 1px solid rgba(255,255,255,.18);
            color: #f8fafc;
        }

        .badge-day{
            background: linear-gradient(
                135deg,
                rgba(34,197,94,.35),
                rgba(34,197,94,.18)
            );
        }

        .badge-night{
            background: linear-gradient(
                135deg,
                rgba(96,165,250,.35),
                rgba(96,165,250,.18)
            );
        }

        .badge-day .dot{
            background: var(--good);
            box-shadow: 0 0 12px rgba(34,197,94,.7);
        }

        .badge-night .dot{
            background: var(--warn);
            box-shadow: 0 0 12px rgba(96,165,250,.7);
        }

        /* === EMPTY STATE === */
        .table tbody td[colspan]{
            color: rgba(232,236,255,.65);
        }
    </style>
</head>

<body>
<div class="container py-5 shell">

    <!-- Header -->
    <div class="card-glass topbar mb-4">
        <div class="inner">
            <div class="d-flex align-items-start justify-content-between flex-wrap gap-3">
                <div>
                    <h1 class="h3 mb-1 fw-bold">ISS Monitoring Dashboard</h1>
                </div>
                <div class="text-end">
                    <div class="helper">Всего на странице: <span class="mono">{{ $records->count() }}</span></div>
                </div>
            </div>
        </div>
    </div>

    <!-- Filters -->
    <div class="card-glass p-4 mb-4">
        <form method="GET" action="/" class="row g-3 align-items-end">
            <div class="col-md-5">
                <label class="form-label subtitle">Поиск</label>
                <input
                    type="text"
                    name="search"
                    class="form-control"
                    placeholder="visibility / latitude / longitude…"
                    value="{{ $search }}"
                >
            </div>

            <div class="col-md-3">
                <label class="form-label subtitle">Сортировать по</label>
                <select name="sort_by" class="form-select">
                    <option value="fetched_at" {{ $sortBy == 'fetched_at' ? 'selected' : '' }}>Дата получения</option>
                    <option value="latitude" {{ $sortBy == 'latitude' ? 'selected' : '' }}>Широта</option>
                    <option value="longitude" {{ $sortBy == 'longitude' ? 'selected' : '' }}>Долгота</option>
                    <option value="visibility" {{ $sortBy == 'visibility' ? 'selected' : '' }}>Видимость</option>
                    <option value="id" {{ $sortBy == 'id' ? 'selected' : '' }}>ID</option>
                </select>
            </div>

            <div class="col-md-2">
                <label class="form-label subtitle">Порядок</label>
                <select name="sort_order" class="form-select">
                    <option value="desc" {{ $sortOrder == 'desc' ? 'selected' : '' }}>Новые сверху</option>
                    <option value="asc" {{ $sortOrder == 'asc' ? 'selected' : '' }}>Старые сверху</option>
                </select>
            </div>

            <div class="col-md-2 d-grid">
                <button type="submit" class="btn btn-accent">Применить</button>
            </div>
        </form>
    </div>

    <!-- Table -->
    <div class="card-glass table-wrap">
        <table class="table table-hover align-middle">
            <thead>
                <tr>
                    <th style="width:90px;">ID</th>
                    <th>Широта</th>
                    <th>Долгота</th>
                    <th style="width:170px;">Видимость</th>
                    <th style="width:210px;">Время (UTC)</th>
                </tr>
            </thead>
            <tbody>
                @forelse($records as $record)
                    <tr
                        class="fade-row"
                        style="animation-delay: {{ ($loop->index % 15) * 0.04 }}s"
                    >
                        <td class="mono">#{{ $record['id'] }}</td>
                        <td class="mono">{{ number_format($record['latitude'], 4) }}</td>
                        <td class="mono">{{ number_format($record['longitude'], 4) }}</td>
                        <td>
                            @if(strtolower(trim($record['visibility'])) == 'daylight')
                                <span class="badge-pill badge-day"><span class="dot"></span> День</span>
                            @else
                                <span class="badge-pill badge-night"><span class="dot"></span> Ночь/Тень</span>
                            @endif
                        </td>
                        <td class="mono">
                            {{ \Carbon\Carbon::parse($record['fetched_at'])->utc()->format('d.m.Y H:i:s') }}
                        </td>
                    </tr>
                @empty
                <tr>
                    <td colspan="5" class="text-center py-5 subtitle">
                        @if($apiError)
                            Rust API недоступен. Запустите сервис и обновите страницу.
                        @else
                            Данных не найдено.
                        @endif
                    </td>
                </tr>
                @endforelse
            </tbody>
        </table>
    </div>

</div>
</body>
</html>
