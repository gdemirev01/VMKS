from django.urls import path, include

from .views import ProfileList, ProfileDetail, UserProfileDetail, UserProfileUpdate

urlpatterns = [
    path('<int:pk>/', ProfileDetail.as_view()),
    path('', ProfileList.as_view()),
    path('current_profile/update/', UserProfileUpdate.as_view()),
    path('current_profile/', UserProfileDetail.as_view()),
]