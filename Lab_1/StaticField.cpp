#include "Header.h"

static Store g_shop;

size_t ShopId() {
	return g_shop.id;
}

size_t ShopMaxCount() {
	return g_shop.maxProductCount;
}

void SetShop(size_t shopId) {
	Store* shop = TakeStore(shopId - 1);
	g_shop = *shop;
	delete shop;
}


static Mode g_mode = Mode::WAIT;

Mode WorkMode() {
	return g_mode;
}

void SetWorkMode(Mode mode) {
	g_mode = mode;
}
