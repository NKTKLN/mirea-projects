#!/usr/bin/env sh
set -e

cd /var/www/html

# .env
if [ ! -f .env ]; then
  if [ -f .env.example ]; then
    cp .env.example .env
  else
    touch .env
  fi
fi

if [ -z "$APP_KEY" ]; then
  php artisan key:generate --force
fi

composer install --no-interaction --prefer-dist

php artisan migrate --force || true

php artisan config:clear || true
php artisan cache:clear || true

exec "$@"
