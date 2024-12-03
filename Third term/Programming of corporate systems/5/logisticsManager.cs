using System;
using System.Collections.Generic;
using System.Linq;

public class LogisticsManager
{
    private List<Warehouse> warehouses;

    public LogisticsManager(List<Warehouse> warehouses)
    {
        this.warehouses = warehouses;
    }

    public void ProcessDelivery(List<Product> delivery)
    {
        if (delivery == null || delivery.Count == 0)
            throw new ArgumentException("Delivery cannot be null or empty.");

        bool allLongShelfLife = delivery.All(p => p.ExpirationDays >= 30);
        bool allShortShelfLife = delivery.All(p => p.ExpirationDays < 30);

        string targetWarehouseType = allLongShelfLife ? "general" :
                                     allShortShelfLife ? "cold" :
                                     "sorting";

        foreach (var warehouse in warehouses)
        {
            if (warehouse.Type != targetWarehouseType)
                continue;

            try 
            {
                warehouse.AddProducts(delivery);

                LogTransfer(delivery, "supplier", warehouse.Address);
                return;
            }
            catch (Exception)
            {
                continue;
            }
        }

        throw new InvalidOperationException("No suitable warehouse found for this delivery.");
    }

    public void InternalOptimize(params int[] warehouseIds)
    {
        List<Warehouse> warehousesForOptimize = warehouses.FindAll(w => warehouseIds.Contains(w.Id));

        foreach (var warehouse in warehousesForOptimize)
        {
            if (warehouse.Type != "sorting")
                continue;

            var toMove = new List<Product>(warehouse.StoredProducts);
            warehouse.StoredProducts.Clear();
            foreach (var product in toMove)
            {
                var targetType = product.ExpirationDays < 30 ? "cold" : "general";
                foreach (var targetWarehouse in warehouses)
                {
                    if (targetWarehouse.Type != targetType || targetWarehouse.GetRemainingCapacity() < product.ItemVolume)
                        continue;

                    targetWarehouse.StoredProducts.Add(product);
                    LogTransfer(new List<Product> { product }, warehouse.Address, targetWarehouse.Address);
                    break;
                }
            }
        }
    }

    public void MoveExpiredProducts(params int[] warehouseIds)
    {
        List<Warehouse> fromWarehouses = warehouses.FindAll(w => warehouseIds.Contains(w.Id));

        foreach (var warehouse in fromWarehouses)
        {
            List<Product> expiredProducts = warehouse.StoredProducts.FindAll(p => p.ExpirationDays <= 0);

            foreach (var disposalWarehouse in warehouses)
            {
                if (disposalWarehouse.Type != "disposal" || disposalWarehouse.GetRemainingCapacity() < 1)
                    continue;
                if (expiredProducts.Count == 0)
                    break;

                foreach (var expiredProduct in expiredProducts)
                {
                    try 
                    {
                        MoveProducts(warehouse.Id, disposalWarehouse.Id, new List<int> { expiredProduct.Id });
                        warehouse.StoredProducts.Remove(expiredProduct);
                    }
                    catch (Exception)
                    {
                        break;
                    }
                }
            }

            if (warehouse.StoredProducts.FindAll(p => p.ExpirationDays <= 0).Count > 0)
                throw new InvalidOperationException($"Not enough capacity in disposal warehouses.");
        }
    }

    public void MoveProducts(int fromWarehouseId, int toWarehouseId, List<int> productIds)
    {
        if (productIds.Count == 0)
            throw new ArgumentException("Delivery cannot be empty.");

        Warehouse fromWarehouse = warehouses.Find(w => w.Id == fromWarehouseId);
        Warehouse toWarehouse = warehouses.Find(w => w.Id == toWarehouseId);

        if (fromWarehouse == null || toWarehouse == null)
            throw new KeyNotFoundException($"Warehouse with ID {fromWarehouseId} or {toWarehouseId} not found.");

        List<Product> productsToMove = new List<Product>();
        foreach (var productId in productIds)
        {
            Product product = fromWarehouse.StoredProducts.Find(p => p.Id == productId);
            if (product == null)
                throw new KeyNotFoundException($"Product with ID {productId} not found in warehouse {fromWarehouseId}.");
            
            productsToMove.Add(product);
        }

        toWarehouse.AddProducts(productsToMove);

        foreach (var productId in productIds)
        {
            fromWarehouse.RemoveProduct(productId);
        }

        LogTransfer(productsToMove, fromWarehouse.Address, toWarehouse.Address);
    }

    public void AnalyzeNetwork()
    {
        foreach (var warehouse in warehouses)
        {
            string status = "Проблем нет";
            foreach (var product in warehouse.StoredProducts)
            {
                if (product.ExpirationDays <= 0 && warehouse.Type != "disposal")
                {
                    status = "Необходимо перемещение товара на склад disposal";
                    break;
                }
                else if (product.ExpirationDays < 30 && warehouse.Type != "cold")
                {
                    status = "Необходимо перемещение товара на склад cold";
                    break;
                }
                else if (product.ExpirationDays >= 30 && warehouse.Type == "cold")
                {
                    status = "Необходимо перемещение товара на склад general";
                    break;
                }
                else if ((warehouse.GetRemainingCapacity() != 0 && warehouse.Type == "sorting") || 
                         (product.ExpirationDays > 0 && warehouse.Type == "disposal"))
                { 
                    bool allLongShelfLife = warehouse.StoredProducts.All(p => p.ExpirationDays >= 30);
                    bool allShortShelfLife = warehouse.StoredProducts.All(p => p.ExpirationDays < 30);

                    string wirehouseType = allLongShelfLife ? "general" :
                                                allShortShelfLife ? "cold" :
                                                "general и cold";

                    status = $"Необходимо перемещение товара на склад {wirehouseType}";
                    break;
                }
            }

            Console.WriteLine($"Warehouse {warehouse.Id} status: {status}");
        }
    }

    public decimal CalculateTotalValue(int warehouseId)
    {
        var warehouse = warehouses.Find(w => w.Id == warehouseId);
        if (warehouse == null)
            return 0;

        decimal totalValue = 0;
        foreach (var product in warehouse.StoredProducts)
        {
            totalValue += product.ItemPrice;
        }
        return totalValue;
    }

    private void LogTransfer(List<Product> products, string from, string to)
    {
        foreach (var product in products)
        {
            Console.WriteLine($"Продукт: {product.Name}, объем: {product.ItemVolume * products.Count}, от куда: {from}, куда: {to}");
        }
    }
}
