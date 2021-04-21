#pragma once




#define NO_COPY(ClassName)							\
private:											\
	ClassName(const ClassName&) = delete;			\
	ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static void Create();			\
	static ClassName* Get();		\
	static void Destroy();			\
private:									\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)				\
ClassName* ClassName::m_pInstance = nullptr;		\
void ClassName::Create()							\
{													\
	if(m_pInstance == nullptr)						\
	{												\
		m_pInstance = new ClassName;				\
	}												\
}													\
ClassName* ClassName::Get()							\
{													\
	/*assert(m_pInstance != nullptr);*/					\
	return m_pInstance;								\
}													\
void ClassName::Destroy()							\
{													\
	if (m_pInstance)								\
	{												\
		delete m_pInstance;							\
		m_pInstance = nullptr;						\
	}												\
}