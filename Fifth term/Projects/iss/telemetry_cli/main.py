import csv
import os
import random
from datetime import datetime, timezone
import psycopg2

CSV_OUT_DIR = os.getenv("CSV_OUT_DIR", "/data/csv")

PG = {
    "host": os.getenv("PGHOST", "db"),
    "port": os.getenv("PGPORT", "5432"),
    "user": os.getenv("PGUSER", "monouser"),
    "password": os.getenv("PGPASSWORD", "monopass"),
    "dbname": os.getenv("PGDATABASE", "monolith"),
}

CREATE_TABLE_SQL = """
CREATE TABLE IF NOT EXISTS telemetry_legacy (
    id SERIAL PRIMARY KEY,
    recorded_at TIMESTAMPTZ NOT NULL,
    voltage DOUBLE PRECISION NOT NULL,
    temp DOUBLE PRECISION NOT NULL,
    source_file TEXT NOT NULL,
    created_at TIMESTAMPTZ NOT NULL DEFAULT now()
);
"""

INSERT_SQL = """
INSERT INTO telemetry_legacy
(recorded_at, voltage, temp, source_file)
VALUES (%s, %s, %s, %s);
"""

def generate_row():
    now = datetime.now(timezone.utc)
    return {
        "recorded_at": now,
        "voltage": round(random.uniform(3.2, 12.6), 2),
        "temp": round(random.uniform(-50.0, 80.0), 2),
    }

def ensure_table():
    conn = psycopg2.connect(**PG)
    conn.autocommit = True
    with conn.cursor() as cur:
        cur.execute(CREATE_TABLE_SQL)
    conn.close()

def main():
    os.makedirs(CSV_OUT_DIR, exist_ok=True)

    ts = datetime.now(timezone.utc).strftime("%Y%m%d_%H%M%S")
    filename = f"telemetry_{ts}.csv"
    path = os.path.join(CSV_OUT_DIR, filename)

    row = generate_row()
    row["source_file"] = filename

    with open(path, "w", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["recorded_at", "voltage", "temp", "source_file"]
        )
        writer.writeheader()
        writer.writerow({
            "recorded_at": row["recorded_at"].strftime("%Y-%m-%d %H:%M:%S"),
            "voltage": row["voltage"],
            "temp": row["temp"],
            "source_file": row["source_file"],
        })

    ensure_table()

    with psycopg2.connect(**PG) as conn:
        with conn.cursor() as cur:
            cur.execute(
                INSERT_SQL,
                (
                    row["recorded_at"],
                    row["voltage"],
                    row["temp"],
                    row["source_file"],
                ),
            )
        conn.commit()

    print(f"[telemetry] inserted row from {filename}")

if __name__ == "__main__":
    main()
