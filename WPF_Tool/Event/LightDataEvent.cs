using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using WPF_Tool.Data;
using WPF_Tool.Utility;
using WPF_Tool.Scripts;
using Microsoft.Win32;
using System.IO;
using System.Diagnostics;
using Newtonsoft.Json.Linq;
using WPF_Tool.Math;
using System.Windows.Controls;
using System.Windows;

namespace WPF_Tool
{
    public partial class MainWindow
    {
        private void LightType_Selected(object sender, RoutedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            ComboBox item = sender as ComboBox;
            int comboBoxIndex = item.SelectedIndex;

            selectedHierarchy.lightData.lightType = comboBoxIndex;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
            
        }

        private void DirectionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float dirX;
            bool isSucceeded = float.TryParse(textBox.Text, out dirX);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.direction.x = dirX;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void DirectionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float dirY;
            bool isSucceeded = float.TryParse(textBox.Text, out dirY);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.direction.y = dirY;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void DirectionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float dirZ;
            bool isSucceeded = float.TryParse(textBox.Text, out dirZ);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.direction.z = dirZ;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void LightPositionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float posX;
            bool isSucceeded = float.TryParse(textBox.Text, out posX);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.position.x = posX;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void LightPositionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float posY;
            bool isSucceeded = float.TryParse(textBox.Text, out posY);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.position.y = posY;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void LightPositionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float posZ;
            bool isSucceeded = float.TryParse(textBox.Text, out posZ);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.position.z = posZ;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void AmbientR_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float ambientR;
            bool isSucceeded = float.TryParse(textBox.Text, out ambientR);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.ambient.r = ambientR;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void AmbientG_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float ambientG;
            bool isSucceeded = float.TryParse(textBox.Text, out ambientG);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.ambient.g = ambientG;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void AmbientB_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float ambientB;
            bool isSucceeded = float.TryParse(textBox.Text, out ambientB);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.ambient.b = ambientB;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void AmbientA_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float ambientA;
            bool isSucceeded = float.TryParse(textBox.Text, out ambientA);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.ambient.a = ambientA;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void AmbientIntensity_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (bWindowInit == false)
                return;
            var slider = sender as Slider;

            double value = slider.Value;

            AmbientIntensityTextBox.Text = value.ToString();

            selectedHierarchy.lightData.ambientIntensity = (float)value;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void DiffuseR_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float diffuseR;
            bool isSucceeded = float.TryParse(textBox.Text, out diffuseR);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.diffuse.r = diffuseR;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void DiffuseG_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float diffuseG;
            bool isSucceeded = float.TryParse(textBox.Text, out diffuseG);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.diffuse.g = diffuseG;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void DiffuseB_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float diffuseB;
            bool isSucceeded = float.TryParse(textBox.Text, out diffuseB);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.diffuse.b = diffuseB;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void DiffuseA_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float diffuseA;
            bool isSucceeded = float.TryParse(textBox.Text, out diffuseA);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.diffuse.a = diffuseA;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void DiffuseIntensity_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (bWindowInit == false)
                return;
            var slider = sender as Slider;

            double value = slider.Value;

            DiffuseIntensityTextBox.Text = value.ToString();

            selectedHierarchy.lightData.diffuseIntensity = (float)value;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void SpecularR_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float specularR;
            bool isSucceeded = float.TryParse(textBox.Text, out specularR);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.specular.r = specularR;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void SpecularG_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float specularG;
            bool isSucceeded = float.TryParse(textBox.Text, out specularG);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.specular.g = specularG;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void SpecularB_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float specularB;
            bool isSucceeded = float.TryParse(textBox.Text, out specularB);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.specular.b = specularB;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void SpecularA_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            TextBox textBox = sender as TextBox;

            float specularA;
            bool isSucceeded = float.TryParse(textBox.Text, out specularA);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.specular.a = specularA;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void SpecularIntensity_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (bWindowInit == false)
                return;

            var slider = sender as Slider;

            double value = slider.Value;

            SpecularIntensityTextBox.Text = value.ToString();

            selectedHierarchy.lightData.specularIntensity = (float)value;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void SpecularPower_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (bWindowInit == false)
                return;

            var slider = sender as Slider;

            double value = slider.Value;

            SpecularPowerTextBox.Text = value.ToString();

            selectedHierarchy.lightData.specularPower = (float)value;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void LightRange_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float range;
            bool isSucceeded = float.TryParse(textBox.Text, out range);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.range = range;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void Cone_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float cone;
            bool isSucceeded = float.TryParse(textBox.Text, out cone);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.cone = cone;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void Constant_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float constant;
            bool isSucceeded = float.TryParse(textBox.Text, out constant);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.constant = constant;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void Linear_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float linear;
            bool isSucceeded = float.TryParse(textBox.Text, out linear);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.linear = linear;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
        private void Quadratic_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bWindowInit == false)
                return;

            TextBox textBox = sender as TextBox;

            float quadratic;
            bool isSucceeded = float.TryParse(textBox.Text, out quadratic);
            if (isSucceeded == false)
                return;

            selectedHierarchy.lightData.quadratic = quadratic;

            Externs.InsertLightData(ref selectedHierarchy.lightData);
        }
    }
}
