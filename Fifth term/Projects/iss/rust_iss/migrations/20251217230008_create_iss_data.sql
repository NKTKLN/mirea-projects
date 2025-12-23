-- Add migration script here
CREATE TABLE IF NOT EXISTS iss_data (
  id SERIAL PRIMARY KEY,
  latitude DOUBLE PRECISION NOT NULL,
  longitude DOUBLE PRECISION NOT NULL,
  visibility TEXT NOT NULL,
  fetched_at TIMESTAMPTZ NOT NULL
);
