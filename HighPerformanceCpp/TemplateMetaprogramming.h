#pragma once

namespace TemplateExamples {
	template<int N, typename T>
	T constPowN(cont T& v) {
		T product{ 1 };
		for (int i = 0; i < N; i++) {
			product *= v;
		}
		return product;
	}
}

