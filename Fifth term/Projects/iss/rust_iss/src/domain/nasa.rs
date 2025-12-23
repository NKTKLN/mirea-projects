use serde::Deserialize;

#[derive(Debug, Deserialize)]
pub struct NasaIssResponse {
    pub latitude: f64,
    pub longitude: f64,
    pub visibility: String,
}
