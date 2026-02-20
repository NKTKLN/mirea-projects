import 'package:flutter/material.dart';
import 'package:flutter_svg/flutter_svg.dart';
import 'package:madshop_ui_kalinin/theme/colors.dart';
import 'package:madshop_ui_kalinin/theme/text_styles.dart';

class ProductItemWidget extends StatelessWidget {
  final String image;
  final String name;
  final double price;
  final bool isFavorite;
  final bool isCartItem;
  final VoidCallback onFavoriteTap;
  final VoidCallback onCartTap;

  const ProductItemWidget({
    super.key,
    required this.image,
    required this.name,
    required this.price,
    this.isFavorite = false,
    this.isCartItem = false,
    required this.onFavoriteTap,
    required this.onCartTap,
  });

  @override
  Widget build(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Container(
          width: 165,
          height: 181,
          decoration: BoxDecoration(
            color: AppColors.white,
            borderRadius: BorderRadius.circular(9),
            boxShadow: [
              BoxShadow(
                color: Colors.black.withValues(alpha: 0.102),
                offset: const Offset(0, 5),
                blurRadius: 10,
              ),
            ],
          ),
          child: Stack(
            children: [
              Positioned(
                top: 0,
                left: 0,
                right: 0,
                bottom: 0,
                child: Center(
                  child: SizedBox(
                    width: 155,
                    height: 171,
                    child: ClipRRect(
                      borderRadius: BorderRadius.circular(5),
                      child: Image.asset(image, fit: BoxFit.cover),
                    ),
                  ),
                ),
              ),
              Positioned(
                top: 10,
                left: 12,
                child: GestureDetector(
                  onTap: onFavoriteTap,
                  child: SvgPicture.asset(
                    'assets/icons/favorite.svg',
                    width: 22,
                    height: 22,
                    colorFilter: ColorFilter.mode(
                      isFavorite ? AppColors.likeActive : AppColors.white,
                      BlendMode.srcIn,
                    ),
                  ),
                ),
              ),
              Positioned(
                bottom: 15,
                left: 12,
                child: GestureDetector(
                  onTap: onCartTap,
                  child: SvgPicture.asset(
                    'assets/icons/cart.svg',
                    width: 22,
                    height: 22,
                    colorFilter: ColorFilter.mode(
                      isCartItem ? AppColors.black : AppColors.white,
                      BlendMode.srcIn,
                    ),
                  ),
                ),
              ),
            ],
          ),
        ),
        const SizedBox(height: 8),
        SizedBox(
          height: 36,
          width: 165,
          child: Text(
            name,
            style: AppTextStyles.productTitle,
            maxLines: 2,
            overflow: TextOverflow.ellipsis,
          ),
        ),
        const SizedBox(height: 4),
        Text(
          '\$${price.toStringAsFixed(2)}',
          style: AppTextStyles.productPrice,
        ),
      ],
    );
  }
}
