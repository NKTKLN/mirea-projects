FROM rust:1.92 AS builder

WORKDIR /app

ENV SQLX_OFFLINE=true


COPY Cargo.toml .
COPY .sqlx ./.sqlx
COPY src ./src
COPY migrations ./migrations

RUN cargo fetch

RUN cargo build --release

# -----------------------------

FROM debian:bookworm-slim
WORKDIR /app

RUN apt-get update \
 && apt-get install -y ca-certificates \
 && rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/target/release/rust_iss /usr/local/bin/rust_iss

EXPOSE 3000
CMD ["rust_iss"]
