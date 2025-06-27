using BlazorClient.Shared;
using System.Net.Http.Json;

namespace BlazorClient.Services
{
    public class ProductService
    {
        private readonly HttpClient _http;

        public ProductService(HttpClient http) => _http = http;

        public async Task<List<Product>> GetProducts() =>
            await _http.GetFromJsonAsync<List<Product>>("api/products") ?? new();

        public async Task AddProduct(Product product) =>
            await _http.PostAsJsonAsync("api/products", product);

        public async Task UpdateProduct(Product product) =>
            await _http.PutAsJsonAsync($"api/products/{product.Id}", product);

        public async Task DeleteProduct(int id) =>
            await _http.DeleteAsync($"api/products/{id}");
    }
}
